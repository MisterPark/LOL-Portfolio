﻿#include "stdafx.h"
#include "Renderer.h"
#include "RenderSystem.h"
#include "FogOfWarRenderSystem.h"
#include<map>
#include<list>
#include<wrl.h>
namespace Engine
{
	wchar_t const* const RENDER_TARGET_RIMLIGHT_COLOR{ L"RT_RIN_LIGHT_COLOR" };
	wchar_t const* const RENDER_TARGET_DEFERRED_RESULT{ L"RT_DEFERRED_RESULT" };
	wchar_t const* const RENDER_TARGET_ALBEDO{ L"RT_ALBEDO" };
	wchar_t const* const RENDER_TARGET_NORMAL{ L"RT_NORMAL" };
	wchar_t const* const RENDER_TARGET_SHARPNESS{ L"RT_SHARPNESS" };
	wchar_t const* const RENDER_TARGET_FOG_OF_WAR{ L"RT_FOG_OF_WAR" };
	wchar_t const* const RENDER_TARGET_HEIGHT_FOG_OF_WAR{ L"RT_HEIGHT_FOG_OF_WAR" };
	wchar_t const* const RENDER_TARGET_SCREEN{ L"RT_SCREEN" };
	wchar_t const* const RENDER_TARGET_SCREEN_ORIGIN{ L"RT_SCREEN_ORIGIN" };

	
	wchar_t const* const LIGHT_SPECULAR = L"light_specular";
	wchar_t const* const LIGHT_DIFFUSE = L"light_diffuse";
	const char ID_TEX_NORMAL_MAP[] = "g_normalMap";
	const char ID_TEX_SPECULAR_MAP[] = "g_specularMap";
	const char ID_CONST_INVERSE_VIEW_PROJ_MATRIX[]{ "g_mInverseViewProj" };
	const char ID_TEX_RIM_LIGHT_COLOR[] = "g_rimLightMap";
	const char ID_TEX_FOR_OF_WAR[] = "g_fogOfWarMap";
	using namespace Microsoft::WRL;
	std::list< Renderer*> rendererTable[(unsigned)RendererType::END];
	struct ShadowMap;
	struct LightAdditionalInfo
	{
		D3DLIGHT9 light;
		Matrix projectionMatrix;
		std::shared_ptr< ShadowMap> shadowMap;
		
	};
	struct ShadowMap
	{
		std::unique_ptr<RenderTarget> renderTarget;
		ComPtr<IDirect3DSurface9> depthBuffer;
	};
	std::set<std::shared_ptr< ShadowMap> > usingShadowMap;
	std::set<std::shared_ptr< ShadowMap> > idleShadowMap;
	long lastUid = 0;
	std::vector<std::wstring> lightNames;
	std::map <std::wstring, LightAdditionalInfo> lights;
	ComPtr<IDirect3DVertexBuffer9> vertexBuffer;
	ComPtr<IDirect3DIndexBuffer9> indexBuffer;

	RenderTarget* albedoRenderTarget;
	RenderTarget* normalRenderTarget;
	RenderTarget* sharpnessRenderTarget;
	RenderTarget* shadowRenderTarget;
	RenderTarget* rimLightColorRenderTarget;
	RenderTarget* fogOfWarRenderTarget;

	RenderTarget* lightSpecularRenderTarget;
	RenderTarget* lightDiffuseRenderTarget;

	ID3DXEffect* renderingShader;
	ID3DXEffect* deferredShader;

	Matrix mViewProj;
	
	ComPtr<ID3DXSprite> sprite_;
	
	struct PPVertexFVF { D3DXVECTOR3 xyz; D3DXVECTOR2 uv; };
	static constexpr DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	auto CompareZ(Renderer* a, Renderer* b)->bool
	{
		return a->transform->zOrder > b->transform->zOrder;
	};
	auto OrderLessZ(Renderer* a, Renderer* b)->bool
	{
		return a->transform->zIndex < b->transform->zIndex;
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
		RenderManager::CreateRenderTarget(RENDER_TARGET_NORMAL, width, height, D3DFMT_A32B32G32R32F);
		RenderManager::CreateRenderTarget(RENDER_TARGET_SHARPNESS, width, height, D3DFMT_A16B16G16R16F);
		RenderManager::CreateRenderTarget(RENDER_TARGET_RIMLIGHT_COLOR, width, height, D3DFMT_A16B16G16R16);
		RenderManager::CreateRenderTarget(RENDER_TARGET_FOG_OF_WAR, 256, 256, D3DFMT_R32F);
		RenderManager::CreateRenderTarget(RENDER_TARGET_SCREEN, width, height, D3DFMT_A8R8G8B8);
		RenderManager::CreateRenderTarget(RENDER_TARGET_SCREEN_ORIGIN, width, height, D3DFMT_A8R8G8B8);
		
		RenderManager::CreateRenderTarget(LIGHT_SPECULAR, width, height, D3DFMT_A16B16G16R16F);
		RenderManager::CreateRenderTarget(LIGHT_DIFFUSE, width, height, D3DFMT_A16B16G16R16F);
		RenderManager::CreateRenderTarget(L"shadow_1", width, height, D3DFMT_A16B16G16R16F);
		shadowRenderTarget = RenderManager::GetRenderTarget(L"shadow_1");
		albedoRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_ALBEDO);
		normalRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_NORMAL);
		sharpnessRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_SHARPNESS);
		rimLightColorRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_RIMLIGHT_COLOR);
		fogOfWarRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_FOG_OF_WAR);
		lightSpecularRenderTarget = RenderManager::GetRenderTarget(LIGHT_SPECULAR);
		lightDiffuseRenderTarget = RenderManager::GetRenderTarget(LIGHT_DIFFUSE);

		renderingShader = RenderManager::LoadEffect(L"./deferred_render.fx");
		deferredShader = RenderManager::LoadEffect(L"./deferred_shader.fx");

		D3DXCreateSprite(device, &sprite_);
		FogOfWarRenderSystem::Initialize();
	}
	void RenderSystem::Destory()
	{
		FogOfWarRenderSystem::Destory();
		indexBuffer.Reset();
		vertexBuffer.Reset();
		idleShadowMap.clear();
		usingShadowMap.clear();
		lights.clear();
		lightNames.clear();
		sprite_ = nullptr;
	}
	void RenderSystem::AddLight(const wchar_t* name, const D3DLIGHT9& init)
	{
		LightAdditionalInfo info{};
		info.light = init;
		lights.emplace(name, info);
		lightNames.emplace_back(name);
	}
	void RenderSystem::RemoveLight(const wchar_t* name)
	{
		lights.erase(name);
		auto const it = std::find(lightNames.begin(), lightNames.end(), name);
		if (it != lightNames.end())
		{
			lightNames.erase(it);
		}
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
			constexpr int _8K = 1024 * 4;
			IDirect3DDevice9* device = RenderManager::GetDevice();
			ComPtr<IDirect3DSurface9> depthBuffer;
			RenderTarget* renderTarget{};
			RenderTarget::Create(_8K, _8K, D3DFMT_G32R32F, &renderTarget);
			//optionTarget
			device->CreateDepthStencilSurface(_8K, _8K, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, false, &depthBuffer, nullptr);
			std::shared_ptr<ShadowMap> shadowMap = std::make_shared<ShadowMap>();
			shadowMap->depthBuffer = depthBuffer;
			shadowMap->renderTarget.reset(renderTarget);
			idleShadowMap.insert(std::move(shadowMap));
		}
		auto idleShadowMapsIt = idleShadowMap.begin();
		std::shared_ptr<ShadowMap> shadowMap = *idleShadowMapsIt;
		it->second.shadowMap = shadowMap;
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
		lastUid = 0;
		IDirect3DDevice9* device = RenderManager::GetDevice();
		device->BeginScene();
		//device->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 0, 1.f, 0);
		device->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 0xFFFFFFFF, 1.f, 0);
		mViewProj = Camera::main->GetViewMatrix() * Camera::main->GetProjectionMatrix();
		FogOfWarRenderSystem::Begin();
		
		RednerEarlyForward();

		FogOfWarRenderSystem::End();


		SetupShadowMap();
		RednerDeferred();
		


		RenderLigting();
		RenderCombine();

		RenderForward();

		RenderPostProcessing();

		RenderUI();
#pragma region DEBUG_SHOW_RENDERTARGET

		const int width = MainGame::GetInstance()->width;
		const int height = MainGame::GetInstance()->height;

		ComPtr<IDirect3DTexture9> texture;
		RenderManager::GetRenderTarget(RENDER_TARGET_HEIGHT_FOG_OF_WAR)->GetTexture(&texture);
		D3DXMATRIX mMatrix;
		D3DXMATRIX mRotate;
		D3DXMATRIX mTranslation;
		D3DXMATRIX mPos;
		D3DXVECTOR3 vCenter{ 128.f, 128.f,0.f };
		D3DXMatrixScaling(&mMatrix, 0.125f, 0.125f , 1.f);
		D3DXMatrixTranslation(&mTranslation, 256.f, 0.f, 0.f);
		sprite_->Begin(D3DXSPRITE_ALPHABLEND);
		sprite_->SetTransform(&mMatrix);
		sprite_->Draw(texture.Get(), nullptr, &vCenter, nullptr, D3DCOLOR_COLORVALUE(1.f, 0.f, 0.f, 1.f));
		
		mMatrix = mTranslation;
		sprite_->SetTransform(&mMatrix);
		texture.Reset();
		RenderManager::GetRenderTarget(RENDER_TARGET_FOG_OF_WAR)->GetTexture(&texture);
		sprite_->Draw(texture.Get(), nullptr, nullptr, nullptr, D3DCOLOR_COLORVALUE(1.f, 0.f, 0.f, 1.f));
		sprite_->End();
		
#pragma endregion

		device->EndScene();
		device->Present(nullptr, nullptr, nullptr, nullptr);
	}
	bool RenderSystem::GetShadowMap(const wchar_t* lightName, RenderTarget** renderTarget,  IDirect3DSurface9** depthBufferOut , Matrix* proj)
	{
		auto findIt = lights.find(lightName);
		if (findIt == lights.end())
		{
			return false;
		}
		if (findIt->second.shadowMap == nullptr)
		{
			return false;
		}
		IDirect3DSurface9* depthBuffer = findIt->second.shadowMap->depthBuffer.Get();
		depthBuffer->AddRef();
		*depthBufferOut = depthBuffer;
		*renderTarget = findIt->second.shadowMap->renderTarget.get();
		*proj = findIt->second.projectionMatrix;
		return true;
	}
	long RenderSystem::GetUniqueID()
	{
		return InterlockedIncrement(&lastUid);
	}
	void RenderSystem::SetupPostProcessing()
	{
		IDirect3DDevice9* const device = RenderManager::GetDevice();
		device->SetFVF(FVF);
		device->SetIndices(indexBuffer.Get());
		device->SetStreamSource(0, vertexBuffer.Get(), 0, sizeof(PPVertexFVF));
	}
	void RenderSystem::ExecutePostProcessing()
	{
		HRESULT hr{};
		IDirect3DDevice9* const device = RenderManager::GetDevice();
		hr = device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
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
		ComPtr<IDirect3DSurface9> oldBackbuffer;
		device->GetDepthStencilSurface(&oldBackbuffer);
		//사용중인 모든 셰도우맵의 깊이값을 1.f으로 맞춘다.
		for (auto& shadowMap : usingShadowMap)
		{
			ComPtr<IDirect3DSurface9> surface;
			ComPtr<IDirect3DSurface9> optionSurface;
			shadowMap->renderTarget->GetSurface(&surface);

			device->SetRenderTarget(0, surface.Get());
			device->SetDepthStencilSurface(shadowMap->depthBuffer.Get());
			device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(1.f, 1.f, 1.f, 1.f), 1.f, 0);
		}
		device->SetDepthStencilSurface(oldBackbuffer.Get());

		float cameraZ = 10.f;
		//최대한 카메라에 가까이에 라이트의 위치를 잡아주고 싶다.
		Transform* cameraTransform = Camera::main->GetTransform();
		Matrix mCameraTransform = Matrix::Inverse(Camera::main->GetViewMatrix());
		Matrix mProjSpace = Camera::main->GetProjectionMatrix();
		Matrix mProjInverse = Matrix::Inverse(mProjSpace);
		Vector3 vCameraPosition = (Vector3&)mCameraTransform.m[3];
		for (auto& pair : lights)
		{
			if (pair.second.shadowMap == nullptr)
			{
				continue;
			}
			
			Vector3 focusAt =
				(Vector3&)mCameraTransform.m[2] * cameraZ
				+ (Vector3&)mCameraTransform.m[3];
			const D3DLIGHT9& light = pair.second.light;
			Vector3 lightPosition = focusAt - 1000.f * (Vector3&)light.Direction;
			Matrix mView;
			Matrix mProjection;
			D3DXMatrixLookAtLH(&mView, &lightPosition, &focusAt, &(Vector3&)mCameraTransform.m[1]);
			//mView = Camera::main->GetViewMatrix();
			//D3DXMatrixPerspectiveFovLH(&mProjection, D3DX_PI * 0.75f, 1.f, 0.1f, 2000.f);
			D3DXMatrixOrthoLH(&mProjection, 1000.f * vCameraPosition.y / 1000.f, 1000.f * vCameraPosition.y / 1000.f, 0.1f, 2000.f);
			pair.second.projectionMatrix = mView * mProjection;
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
		IDirect3DDevice9* const device = RenderManager::GetDevice();
		device->Clear(0, nullptr,  D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(1.f, 1.f, 1.f, 1.f), 1.f, 0);
	}
	void RenderSystem::RednerDeferred()
	{
		IDirect3DDevice9* device = RenderManager::GetDevice();
		
		ComPtr<IDirect3DSurface9> albedoSurface;
		ComPtr<IDirect3DSurface9> normalSurface;
		ComPtr<IDirect3DSurface9> sharpnessSurface;
		ComPtr<IDirect3DSurface9> rimLightSurface;
		albedoRenderTarget->GetSurface(&albedoSurface);
		normalRenderTarget->GetSurface(&normalSurface);
		sharpnessRenderTarget->GetSurface(&sharpnessSurface);
		rimLightColorRenderTarget->GetSurface(&rimLightSurface);
		device->SetRenderTarget(0, albedoSurface.Get());
		device->SetRenderTarget(1, normalSurface.Get());
		device->SetRenderTarget(2, sharpnessSurface.Get());
		device->SetRenderTarget(3, rimLightSurface.Get());
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
	void RenderSystem::RenderPostProcessing()
	{
		HRESULT hr{};
		IDirect3DDevice9* device = RenderManager::GetDevice();
		auto& PPEfects = rendererTable[(unsigned)RendererType::PostProcessEffect];
		PPEfects.sort(CompareZ);

		RenderTarget* screen = RenderManager::GetRenderTarget(RENDER_TARGET_SCREEN);
		
		for (auto* processingRenderer : PPEfects)
		{
			ComPtr<IDirect3DSurface9> screenTexture;
			ComPtr<IDirect3DSurface9> backbuffer;
			device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
			screen->GetSurface(&screenTexture);
			hr = device->StretchRect(backbuffer.Get(), nullptr, screenTexture.Get(), nullptr, D3DTEXF_NONE);
			processingRenderer->Render();
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
		SetupPostProcessing();
		UINT passCount = 0;

		deferredShader->Begin(&passCount, 0);

		D3DXVECTOR4 vCameraPosition{ Camera::main->GetPosition(), 1.f };
		Matrix	mInverseViewProj;
		Matrix  mView = Camera::main->GetViewMatrix();
		ComPtr<IDirect3DTexture9> albedoTexture{};
		ComPtr<IDirect3DTexture9> normalTexture{};
		ComPtr<IDirect3DTexture9> sharpnessTexture{};
		ComPtr<IDirect3DTexture9> lightDiffuseTexture{};
		ComPtr<IDirect3DTexture9> lightSpecularTexture{};
		ComPtr<IDirect3DTexture9> fogOfWarTexture{};
		ComPtr<IDirect3DTexture9> rimLightColorTexture{};
		ComPtr<IDirect3DSurface9> lightDiffuseSurface{};
		ComPtr<IDirect3DSurface9> lightSpecularSurface{};
		ComPtr<IDirect3DSurface9> shadowSurface{};
		D3DXMatrixInverse(&mInverseViewProj, nullptr, &mViewProj);
		deferredShader->SetMatrix(ID_CONST_INVERSE_VIEW_PROJ_MATRIX, &mInverseViewProj);

		normalRenderTarget->GetTexture(&normalTexture);
		sharpnessRenderTarget->GetTexture(&sharpnessTexture);
		albedoRenderTarget->GetTexture(&albedoTexture);
		rimLightColorRenderTarget->GetTexture(&rimLightColorTexture);
		RenderManager::GetRenderTarget(L"FogOfWarRenderSystem_Blur2")->GetTexture(&fogOfWarTexture);
		deferredShader->SetTexture(ID_TEX_NORMAL_MAP, normalTexture.Get());
		deferredShader->SetTexture(ID_TEX_SPECULAR_MAP, sharpnessTexture.Get());
		deferredShader->SetTexture("g_albedoMap", albedoTexture.Get());
		lightDiffuseRenderTarget->GetSurface(&lightDiffuseSurface);
		lightSpecularRenderTarget->GetSurface(&lightSpecularSurface);
		shadowRenderTarget->GetSurface(&shadowSurface);

		device->SetRenderTarget(0, lightDiffuseSurface.Get());
		device->SetRenderTarget(1, lightSpecularSurface.Get());
		device->SetRenderTarget(2, nullptr);
		device->SetRenderTarget(3, nullptr);
		device->Clear(0, nullptr, D3DCLEAR_TARGET, 0, 0, 0);

		deferredShader->SetVector("g_vCameraPosition", &vCameraPosition);

		for (auto const& pair : lights)
		{
			D3DLIGHT9 const& light = pair.second.light;
			int passNum = 0;
			switch (light.Type)
			{
			case D3DLIGHT_DIRECTIONAL:
				passNum = 2;
				{
					if (pair.second.shadowMap != nullptr)
					{
						passNum = 1;
						ComPtr<IDirect3DTexture9> texture;
						ComPtr<IDirect3DTexture9> shdowOptionTexture;
						pair.second.shadowMap->renderTarget->GetTexture(&texture);
						deferredShader->SetTexture("g_shadowMap", texture.Get());
						deferredShader->SetMatrix("g_mLightSpace", &pair.second.projectionMatrix);
					}
					D3DXVECTOR4 vLightDir = D3DXVECTOR4(light.Direction, 0.f);
					D3DXVec4Transform(&vLightDir, &vLightDir, &mView);
					vLightDir.w = 1.f;
					deferredShader->SetVector("g_vLightDirectionAndPower", &vLightDir);
					deferredShader->SetVector("g_vLightAmbient", reinterpret_cast<D3DXVECTOR4 const*>(&light.Ambient));
					deferredShader->SetVector("g_vLightDiffuse", reinterpret_cast<D3DXVECTOR4 const*>(&light.Diffuse));

				}
				break;
			}
			if (passNum == 0)continue;
			deferredShader->BeginPass(passNum);
			ExecutePostProcessing();
			deferredShader->EndPass();
		}
		deferredShader->End();
	}
	void RenderSystem::RenderCombine()
	{
		IDirect3DDevice9* const device = RenderManager::GetDevice();
		ComPtr<IDirect3DTexture9> albedoTexture{};
		ComPtr<IDirect3DTexture9> normalTexture{};
		ComPtr<IDirect3DTexture9> sharpnessTexture{};
		ComPtr<IDirect3DTexture9> lightDiffuseTexture{};
		ComPtr<IDirect3DTexture9> lightSpecularTexture{};
		ComPtr<IDirect3DTexture9> fogOfWarTexture{};
		ComPtr<IDirect3DTexture9> rimLightColorTexture{};
		ComPtr<IDirect3DSurface9> lightDiffuseSurface{};
		ComPtr<IDirect3DSurface9> lightSpecularSurface{};
		ComPtr<IDirect3DSurface9> shadowSurface{};
		Matrix  mView = Camera::main->GetViewMatrix();

		normalRenderTarget->GetTexture(&normalTexture);
		sharpnessRenderTarget->GetTexture(&sharpnessTexture);
		albedoRenderTarget->GetTexture(&albedoTexture);
		rimLightColorRenderTarget->GetTexture(&rimLightColorTexture);
		RenderManager::GetRenderTarget(L"FogOfWarRenderSystem_Blur2")->GetTexture(&fogOfWarTexture);
		deferredShader->SetTexture(ID_TEX_NORMAL_MAP, normalTexture.Get());
		deferredShader->SetTexture(ID_TEX_SPECULAR_MAP, sharpnessTexture.Get());
		deferredShader->SetTexture("g_albedoMap", albedoTexture.Get());
		lightDiffuseRenderTarget->GetSurface(&lightDiffuseSurface);
		lightSpecularRenderTarget->GetSurface(&lightSpecularSurface);
		shadowRenderTarget->GetSurface(&shadowSurface);


		D3DXVECTOR4 screenSize{ (float)MainGame::GetInstance()->width, (float)MainGame::GetInstance()->height,1.f, 1.f };
		D3DXVECTOR4 texelKernel[]{
			{0	,	+2.f / screenSize.y,0,0},
			{0	,	-2.f / screenSize.y,0,0},
			{+2.f / screenSize.x	,	0,0,0},
			{-2.f / screenSize.x	,	0,0,0},
			{0	,	+1.f / screenSize.y,0,0},
			{0	,	-1.f / screenSize.y,0,0},
			{+1.f / screenSize.x	,	0,0,0},
			{-1.f / screenSize.x	,	0,0,0}
		};

		ComPtr<IDirect3DSurface9> backbuffer;
		Matrix mFogOfWarSpace{};
		FogOfWarRenderSystem::GetMapSpace(&mFogOfWarSpace);

		device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
		device->SetRenderTarget(0, backbuffer.Get());
		device->SetRenderTarget(1, nullptr);
		device->SetRenderTarget(2, nullptr);
		device->SetRenderTarget(3, nullptr);
		lightDiffuseRenderTarget->GetTexture(&lightDiffuseTexture);
		lightSpecularRenderTarget->GetTexture(&lightSpecularTexture);
		deferredShader->SetMatrix("g_mView", &mView);
		deferredShader->SetMatrix("g_mForOfWarSpace", &mFogOfWarSpace);
		deferredShader->SetTexture("g_shadeMap", lightDiffuseTexture.Get());
		deferredShader->SetTexture("g_specularMap", lightSpecularTexture.Get());
		deferredShader->SetTexture(ID_TEX_RIM_LIGHT_COLOR, rimLightColorTexture.Get());
		deferredShader->SetTexture(ID_TEX_FOR_OF_WAR, fogOfWarTexture.Get());

		deferredShader->SetVectorArray("TexelKernel", texelKernel, 8);
		deferredShader->SetTexture(ID_TEX_NORMAL_MAP, normalTexture.Get());


		UINT passCount = 0;
		SetupPostProcessing();
		deferredShader->Begin(&passCount, 0);
		deferredShader->BeginPass(0);
		ExecutePostProcessing();
		deferredShader->EndPass();
		deferredShader->End();
	}
	void Engine::RenderSystem::Add(Renderer* renderer)
	{
		auto& renderers = rendererTable[(unsigned)renderer->rendererType];
		auto findIt = std::find(renderers.begin(), renderers.end(), renderer);
		if (findIt != renderers.end())
		{
			return;
		}
		renderers.emplace_back(renderer);
	}

	void Engine::RenderSystem::Remove(Renderer* renderer)
	{
		auto& renderers = rendererTable[(unsigned)renderer->rendererType];
		renderers.remove(renderer);
		//auto findIt = std::find(renderers.begin(), renderers.end(), renderer);
		//if (findIt == renderers.end())
		//{
		//	return;
		//}
		//
		//renderers.erase(findIt);
	}
}
