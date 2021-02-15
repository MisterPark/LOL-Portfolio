#include "stdafx.h"
#include "Renderer.h"
#include "RenderSystem.h"
#include<map>
#include<list>
#include<wrl.h>
namespace KST
{
	wchar_t const* const RENDER_TARGET_DEFERRED_RESULT{ L"RT_DEFERRED_RESULT" };
	wchar_t const* const RENDER_TARGET_ALBEDO{ L"RT_ALBEDO" };
	wchar_t const* const RENDER_TARGET_NORMAL{ L"RT_NORMAL" };
	wchar_t const* const RENDER_TARGET_DEPTH{ L"RT_DEPTH" };
	wchar_t const* const RENDER_TARGET_SHARPNESS{ L"RT_SHARPNESS" };
	wchar_t const* const LIGHT_SPECULAR = L"light_specular";
	wchar_t const* const LIGHT_DIFFUSE = L"light_diffuse";
	const char ID_TEX_NORMAL_MAP[] = "g_normalMap";
	const char ID_TEX_SPECULAR_MAP[] = "g_specularMap";
	const char ID_CONST_INVERSE_VIEW_PROJ_MATRIX[]{ "g_mInverseViewProj" };
	const char ID_TEX_DEPTH_MAP[]{ "g_depthMap" };
	using namespace Microsoft::WRL;
	std::list< Renderer*> rendererTable[(unsigned)RendererType::END];
	struct LightAdditionalInfo
	{
		D3DLIGHT9 light;
		Matrix projectionMatrix;
		RenderTarget* shadowMap;
	};

	std::set<RenderTarget*> usingShadowMap;
	std::set<RenderTarget*> idleShadowMap;

	std::vector<std::wstring> lightNames;
	std::map <std::wstring, LightAdditionalInfo> lights;
	ComPtr<IDirect3DVertexBuffer9> vertexBuffer;
	ComPtr<IDirect3DIndexBuffer9> indexBuffer;

	RenderTarget* albedoRenderTarget;
	RenderTarget* normalRenderTarget;
	RenderTarget* sharpnessRenderTarget;
	RenderTarget* depthRenderTarget;

	RenderTarget* lightSpecularRenderTarget;
	RenderTarget* lightDiffuseRenderTarget;

	ID3DXEffect* renderingShader;
	ID3DXEffect* deferredShader;

	Matrix mViewProj;

	struct PPVertexFVF { D3DXVECTOR3 xyz; D3DXVECTOR2 uv; };
	static constexpr DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	auto CompareZ(Renderer* a, Renderer* b)->bool
	{
		return a->transform->zOrder > b->transform->zOrder;
	};
	auto OrderLessZ(Renderer* a, Renderer* b)->bool
	{
		return a->transform->zOrder < b->transform->zOrder;
	};
	void RenderSystem::Initialize()
	{
		IDirect3DDevice9* device = RenderManager::GetDevice();
		device->CreateVertexBuffer(sizeof(PPVertexFVF) * 4, 0, FVF, D3DPOOL_MANAGED, &vertexBuffer, nullptr);
		device->CreateIndexBuffer(sizeof(int) * 6, 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &indexBuffer, nullptr);
		PPVertexFVF* pVertices;
		vertexBuffer->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);
		pVertices[0].uv = D3DXVECTOR2{ 0.f, 0.f };
		pVertices[0].xyz = D3DXVECTOR3{ -1.f, 1.f, 0.f };

		pVertices[1].uv = D3DXVECTOR2{ 1.f, 0.f };
		pVertices[1].xyz = D3DXVECTOR3{ 1.f, 1.f, 0.f };

		pVertices[2].uv = D3DXVECTOR2{ 1.f, 1.f };
		pVertices[2].xyz = D3DXVECTOR3{ 1.f, -1.f, 0.f };

		pVertices[3].uv = D3DXVECTOR2{ 0.f, 1.f };
		pVertices[3].xyz = D3DXVECTOR3{ -1.f, -1.f, 0.f };
		vertexBuffer->Unlock();
		int* pIndices;
		indexBuffer->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

		pIndices[0] = 0;
		pIndices[1] = 1;
		pIndices[2] = 3;

		pIndices[3] = 1;
		pIndices[4] = 2;
		pIndices[5] = 3;

		indexBuffer->Unlock();

		const int width = MainGame::GetInstance()->width;
		const int height = MainGame::GetInstance()->height;
		RenderManager::CreateRenderTarget(RENDER_TARGET_ALBEDO, width, height, D3DFMT_A8R8G8B8);
		RenderManager::CreateRenderTarget(RENDER_TARGET_NORMAL, width, height, D3DFMT_A16B16G16R16F);
		RenderManager::CreateRenderTarget(RENDER_TARGET_SHARPNESS, width, height, D3DFMT_A16B16G16R16F);
		RenderManager::CreateRenderTarget(RENDER_TARGET_DEPTH, width, height, D3DFMT_G32R32F);
		RenderManager::CreateRenderTarget(LIGHT_SPECULAR, width, height, D3DFMT_A16B16G16R16F);
		RenderManager::CreateRenderTarget(LIGHT_DIFFUSE, width, height, D3DFMT_A16B16G16R16F);
		albedoRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_ALBEDO);
		normalRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_NORMAL);
		sharpnessRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_SHARPNESS);
		depthRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_DEPTH);
		lightSpecularRenderTarget = RenderManager::GetRenderTarget(LIGHT_SPECULAR);
		lightDiffuseRenderTarget = RenderManager::GetRenderTarget(LIGHT_DIFFUSE);

		renderingShader = RenderManager::LoadEffect(L"./deferred_render.fx");
		deferredShader = RenderManager::LoadEffect(L"./deferred_shader.fx");
	}
	void RenderSystem::Destory()
	{
		indexBuffer.Reset();
		vertexBuffer.Reset();
		for (auto it : usingShadowMap)
		{
			delete it;
		}
		for (auto it : idleShadowMap)
		{
			delete it;
		}
	}
	void RenderSystem::AddLight(const wchar_t* name, const D3DLIGHT9& init)
	{
		LightAdditionalInfo info{};
		info.light = init;
		lights.emplace(name, info);
	}
	void RenderSystem::RemoveLight(const wchar_t* name)
	{
		lights.erase(name);
	}
	D3DLIGHT9* RenderSystem::GetLight(const wchar_t* name)
	{
		auto findIt = lights.find(name);
		if (findIt == lights.end())
		{
			return nullptr;
		}
		return &findIt->second.light;
	}
	int RenderSystem::GetLightCount()
	{
		return static_cast<int>(lights.size());
	}
	void RenderSystem::GetLights(D3DLIGHT9* buffer, int count)
	{
		D3DLIGHT9* const end = buffer + count;
		D3DLIGHT9* it = buffer;
		for (auto pair : lights)
		{
			if (it == end)
			{
				break;
			}
			*it = pair.second.light;
			++it;
		}
	}
	wstring const& RenderSystem::GetLightName(int index)
	{
		return lightNames[index];
	}
	void RenderSystem::EnableShadow(const wchar_t* lightName)
	{
		auto it = lights.find(lightName);
		if (it == lights.end())
		{
			return;
		}
		if (it->second.light.Type != D3DLIGHT_DIRECTIONAL)
		{
			return;
		}
		if (it->second.shadowMap != nullptr)
		{
			return;
		}
		if (idleShadowMap.empty())
		{
			RenderTarget* renderTarget{};
			RenderTarget::Create(2048, 2048, D3DFMT_G32R32F, &renderTarget);
			idleShadowMap.insert(renderTarget);
		}
		auto idleShadowMapsIt = idleShadowMap.begin();
		RenderTarget* shadowMap = *idleShadowMapsIt;
		idleShadowMap.erase(idleShadowMapsIt);
		usingShadowMap.emplace(shadowMap);
	}
	void RenderSystem::DisableShadow(const wchar_t* lightName)
	{
		auto it = lights.find(lightName);
		if (it == lights.end())
		{
			return;
		}
		if (it->second.shadowMap == nullptr)
		{
			return;
		}
		idleShadowMap.emplace(it->second.shadowMap);
		usingShadowMap.erase(it->second.shadowMap);
		it->second.shadowMap = nullptr;
	}
	void RenderSystem::Render()
	{
		IDirect3DDevice9* device = RenderManager::GetDevice();
		device->BeginScene();
		//device->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 0, 1.f, 0);
		device->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 0xFFFFFFFF, 1.f, 0);
		RednerEarlyForward();
		SetupShadowMap();
		RednerDeferred();
		RenderLigting();
		RenderCombine();
		RenderForward();
		RenderUI();

		device->EndScene();
		device->Present(nullptr, nullptr, nullptr, nullptr);
	}
	bool RenderSystem::GetShadowMap(const wchar_t* lightName, RenderTarget** renderTarget, Matrix* proj)
	{
		return false;
	}
	void RenderSystem::SetupShadowMap()
	{
		IDirect3DDevice9* const device = RenderManager::GetDevice();
		for (auto& pair : lights)
		{
			D3DLIGHT9& light = pair.second.light;
			if (light.Type != D3DLIGHT_DIRECTIONAL)
			{
				DisableShadow(pair.first.c_str());
				continue;
			}

		}
		//사용중인 모든 셰도우맵의 깊이값을 1.f으로 맞춘다.
		for (auto renderTarget : usingShadowMap)
		{
			ComPtr<IDirect3DSurface9> surface;
			renderTarget->GetSurface(&surface);
			device->SetRenderTarget(0, surface.Get());
			device->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_STENCIL | D3DCLEAR_STENCIL, 0xFFFFFFFF, 1.f, 0);
		}
	}
	void RenderSystem::RednerEarlyForward()
	{
		auto& forwardRenderers = rendererTable[(unsigned)RendererType::EarlyForward];
		//렌더링을 진행한다.
		std::type_info const* prevRendererClass = nullptr;
		for (auto* forwardRenderer : forwardRenderers)
		{
			forwardRenderer->Render();
		}
	}
	void RenderSystem::RednerDeferred()
	{
		IDirect3DDevice9* device = RenderManager::GetDevice();
		ComPtr<IDirect3DSurface9> albedoSurface;
		ComPtr<IDirect3DSurface9> normalSurface;
		ComPtr<IDirect3DSurface9> sharpnessSurface;
		ComPtr<IDirect3DSurface9> depthSurface;
		albedoRenderTarget->GetSurface(&albedoSurface);
		normalRenderTarget->GetSurface(&normalSurface);
		sharpnessRenderTarget->GetSurface(&sharpnessSurface);
		depthRenderTarget->GetSurface(&depthSurface);

		device->SetRenderTarget(0, albedoSurface.Get());
		device->SetRenderTarget(1, normalSurface.Get());
		device->SetRenderTarget(2, sharpnessSurface.Get());
		device->SetRenderTarget(3, depthSurface.Get());
		device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(0.f, 0.f, 0.f, 0.f), 1.f, 0);
		auto& deferredRenderers = rendererTable[(unsigned)RendererType::Deferred];
		for (Renderer* renderer : deferredRenderers)
		{
			renderer->Render();
		}
	}
	void RenderSystem::RenderForward()
	{
		auto& forwardRenderers = rendererTable[(unsigned) RendererType::Forward];
		//정렬을 하고
		forwardRenderers.sort(CompareZ);
		//렌더링을 진행한다.

		for (auto* forwardRenderer : forwardRenderers)
		{
			forwardRenderer->Render();
		}
	}
	void RenderSystem::RenderUI()
	{
		IDirect3DDevice9* const device = RenderManager::GetDevice();
		ComPtr<IDirect3DSurface9> backbuffer;

		device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
		device->SetRenderTarget(0, backbuffer.Get());

		auto& forwardRenderers = rendererTable[(unsigned)RendererType::UI];

		forwardRenderers.sort(OrderLessZ);

		for (auto* forwardRenderer : forwardRenderers)
		{
			forwardRenderer->Render();
		}
	}
	void RenderSystem::RenderLigting()
	{
		IDirect3DDevice9* const device = RenderManager::GetDevice();
		device->SetFVF(FVF);
		device->SetIndices(indexBuffer.Get());
		device->SetStreamSource(0, vertexBuffer.Get(), 0, sizeof(PPVertexFVF));
		UINT passCount = 0;

		deferredShader->Begin(&passCount, 0);

		D3DXVECTOR4 vCameraPosition{ Camera::main->GetPosition(), 1.f };
		Matrix	mInverseViewProj;

		ComPtr<IDirect3DTexture9> albedoTexture{};
		ComPtr<IDirect3DTexture9> normalTexture{};
		ComPtr<IDirect3DTexture9> sharpnessTexture{};
		ComPtr<IDirect3DTexture9> depthTexture{};
		ComPtr<IDirect3DTexture9> lightDiffuseTexture{};
		ComPtr<IDirect3DTexture9> lightSpecularTexture{};

		ComPtr<IDirect3DSurface9> lightDiffuseSurface{};
		ComPtr<IDirect3DSurface9> lightSpecularSurface{};
		D3DXMatrixInverse(&mInverseViewProj, nullptr, &mViewProj);
		deferredShader->SetMatrix(ID_CONST_INVERSE_VIEW_PROJ_MATRIX, &mInverseViewProj);

		normalRenderTarget->GetTexture(&normalTexture);
		sharpnessRenderTarget->GetTexture(&sharpnessTexture);
		depthRenderTarget->GetTexture(&depthTexture);
		albedoRenderTarget->GetTexture(&albedoTexture);

		deferredShader->SetTexture(ID_TEX_NORMAL_MAP, normalTexture.Get());
		deferredShader->SetTexture(ID_TEX_SPECULAR_MAP, sharpnessTexture.Get());
		deferredShader->SetTexture(ID_TEX_DEPTH_MAP, depthTexture.Get());
		deferredShader->SetTexture("g_albedoMap", albedoTexture.Get());

		lightDiffuseRenderTarget->GetSurface(&lightDiffuseSurface);
		lightSpecularRenderTarget->GetSurface(&lightSpecularSurface);
		device->SetRenderTarget(0, lightDiffuseSurface.Get());
		device->SetRenderTarget(1, lightSpecularSurface.Get());

		device->SetRenderTarget(2, nullptr);
		device->SetRenderTarget(3, nullptr);

		deferredShader->SetVector("g_vCameraPosition", &vCameraPosition);


		std::vector<D3DLIGHT9> lights;
		lights.resize(RenderSystem::GetLightCount(), D3DLIGHT9{});
		RenderSystem::GetLights(lights.data(), lights.size());
		for (auto const& light : lights)
		{
			int passNum = 0;
			switch (light.Type)
			{
			case D3DLIGHT_DIRECTIONAL:
				passNum = 1;
				{
					D3DXVECTOR4 vLightDir = D3DXVECTOR4(light.Direction, 1.f);
					deferredShader->SetVector("g_vLightDirectionAndPower", &vLightDir);
					deferredShader->SetVector("g_vLightAmbient", reinterpret_cast<D3DXVECTOR4 const*>(&light.Ambient));
					deferredShader->SetVector("g_vLightDiffuse", reinterpret_cast<D3DXVECTOR4 const*>(&light.Diffuse));
				}
				break;
			}
			if (passNum == 0)continue;
			deferredShader->BeginPass(passNum);
			device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
			deferredShader->EndPass();
		}

		ComPtr<IDirect3DSurface9> backbuffer;

		device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
		device->SetRenderTarget(0, backbuffer.Get());
		device->SetRenderTarget(1, nullptr);
		device->SetRenderTarget(2, nullptr);
		device->SetRenderTarget(3, nullptr);
		lightDiffuseRenderTarget->GetTexture(&lightDiffuseTexture);
		lightSpecularRenderTarget->GetTexture(&lightSpecularTexture);

		deferredShader->SetTexture("g_shadeMap", lightDiffuseTexture.Get());
		deferredShader->SetTexture("g_specularMap", lightSpecularTexture.Get());
		deferredShader->SetTexture("g_depthMap", depthTexture.Get());

		deferredShader->BeginPass(0);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
		deferredShader->EndPass();
		deferredShader->End();
	}
	void RenderSystem::RenderCombine()
	{
	}
	void KST::RenderSystem::Add(Renderer* renderer)
	{
		auto& renderers = rendererTable[(unsigned)renderer->rendererType];
		auto findIt = std::find(renderers.begin(), renderers.end(), renderer);
		if (findIt != renderers.end())
		{
			return;
		}
		renderers.emplace_back(renderer);
	}

	void KST::RenderSystem::Remove(Renderer* renderer)
	{
		auto& renderers = rendererTable[(unsigned)renderer->rendererType];
		auto findIt = std::find(renderers.begin(), renderers.end(), renderer);
		if (findIt == renderers.end())
		{
			return;
		}
		renderers.erase(findIt);
	}
}
