#include "stdafx.h"
#include "GameRendererImpl.h"
#include "RenderManager.h"
#include "Camera.h"
#include "MainGame.h"
wchar_t const* const RENDER_TARGET_ALBEDO{ L"RT_ALBEDO" };
wchar_t const* const RENDER_TARGET_NORMAL{ L"RT_NORMAL" };
wchar_t const* const RENDER_TARGET_DEPTH{ L"RT_DEPTH" };
wchar_t const* const RENDER_TARGET_SPECULAR{ L"RT_SPECULAR" };
wchar_t const* const LIGHT_SPECULAR = L"light_specular";
wchar_t const* const LIGHT_DIFFUSE = L"light_diffuse";

const char ID_TEX_NORMAL_MAP[] = "g_normalMap";
const char ID_TEX_SPECULAR_MAP[] = "g_specularMap";
const char ID_CONST_INVERSE_VIEW_PROJ_MATRIX[]{ "g_mInverseViewProj" };
const char ID_TEX_DEPTH_MAP[]{ "g_depthMap" };

struct PPVertexFVF { D3DXVECTOR3 xyz; D3DXVECTOR2 uv; };
static constexpr DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
GameRendererImpl::GameRendererImpl()
{
	IDirect3DDevice9* device = RenderManager::GetDevice();
	HRESULT hr{};
	MainGame* const game = MainGame::GetInstance();
	RenderManager::CreateRenderTarget(RENDER_TARGET_ALBEDO, game->width, game->height, D3DFMT_A8R8G8B8);
	RenderManager::CreateRenderTarget(RENDER_TARGET_NORMAL, game->width, game->height, D3DFMT_A16B16G16R16F);
	RenderManager::CreateRenderTarget(RENDER_TARGET_SPECULAR, game->width, game->height, D3DFMT_A16B16G16R16F);
	RenderManager::CreateRenderTarget(RENDER_TARGET_DEPTH, game->width, game->height, D3DFMT_G32R32F);
	RenderManager::CreateRenderTarget(LIGHT_SPECULAR, game->width, game->height, D3DFMT_A16B16G16R16F);
	RenderManager::CreateRenderTarget(LIGHT_DIFFUSE, game->width, game->height, D3DFMT_A16B16G16R16F);

	device->CreateVertexBuffer(sizeof(PPVertexFVF) * 4, 0, FVF, D3DPOOL_MANAGED, &vertexBuffer_, nullptr);
	device->CreateIndexBuffer(sizeof(int) * 6, 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &indexBuffer_, nullptr);
	PPVertexFVF* pVertices;
	vertexBuffer_->Lock(0, 0, reinterpret_cast<void**>(&pVertices), 0);
	pVertices[0].uv = D3DXVECTOR2{ 0.f, 0.f };
	pVertices[0].xyz = D3DXVECTOR3{ -1.f, 1.f, 0.f };

	pVertices[1].uv = D3DXVECTOR2{ 1.f, 0.f };
	pVertices[1].xyz = D3DXVECTOR3{ 1.f, 1.f, 0.f };

	pVertices[2].uv = D3DXVECTOR2{ 1.f, 1.f };
	pVertices[2].xyz = D3DXVECTOR3{ 1.f, -1.f, 0.f };

	pVertices[3].uv = D3DXVECTOR2{ 0.f, 1.f };
	pVertices[3].xyz = D3DXVECTOR3{ -1.f, -1.f, 0.f };
	vertexBuffer_->Unlock();
	int* pIndices;
	indexBuffer_->Lock(0, 0, reinterpret_cast<void**>(&pIndices), 0);

	pIndices[0] = 0;
	pIndices[1] = 1;
	pIndices[2] = 3;

	pIndices[3] = 1;
	pIndices[4] = 2;
	pIndices[5] = 3;

	indexBuffer_->Unlock();
	ComPtr<ID3DXBuffer> msgBuffer;
	hr = D3DXCreateEffectFromFileW(
		device,
		L"./deferred_shader.fx",
		nullptr,
		nullptr,
		D3DXSHADER_OPTIMIZATION_LEVEL3,
		nullptr,
		&deferredShader_,
		&msgBuffer
	);
	ComPtr<ID3DXEffect> effect;
	msgBuffer = ComPtr<ID3DXBuffer>{};
	effect = ComPtr<ID3DXEffect>{};
	hr = D3DXCreateEffectFromFileW(
		device,
		L"./deferred_render.fx",
		nullptr,
		nullptr,
		D3DXSHADER_OPTIMIZATION_LEVEL3,
		nullptr,
		&effect,
		&msgBuffer
	);
	effects_.emplace(L"DEFERRED", effect);
}

void GameRendererImpl::Register(RenderGroupID groupId, PKH::GameObject* object)
{
	std::list<GameObject*>& group = renderGroups_[groupId];
	auto it = std::find(group.begin(), group.end(), object);
	if (it != group.end())
	{
		return;
	}
	group.emplace_back(object);
}

void GameRendererImpl::Unregister(RenderGroupID groupId, PKH::GameObject* object)
{
	std::list<GameObject*>& group = renderGroups_[groupId];
	auto it = std::find(group.begin(), group.end(), object);
	if (it == group.end())
	{
		return;
	}
	group.erase(it);
}

void GameRendererImpl::Render()
{
	Matrix mViewSpace = Camera::main->GetViewMatrix();
	Matrix mProjSpace = Camera::main->GetProjectionMatrix();
	mViewProj = mViewSpace * mProjSpace;
	IDirect3DDevice9* const device = RenderManager::GetDevice();
	for (auto& pair : effects_)
	{
		ID3DXEffect* effect = pair.second.Get();
		effect->SetMatrix("g_mViewSpace",		&mViewSpace);
		effect->SetMatrix("g_mProjSpace",		&mProjSpace);
		effect->SetMatrix("g_mViewProjSpace",	&mViewProj);
	}
	device->SetTransform(D3DTS_PROJECTION, reinterpret_cast<D3DMATRIX*>(&mProjSpace));
	device->SetTransform(D3DTS_VIEW, reinterpret_cast<D3DMATRIX*>(&mViewSpace));
	device->BeginScene();
	device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, 0, 1.f, 0);
	DeferredRender();
	RenderUI();
	device->EndScene();
	device->Present(nullptr, nullptr, nullptr, nullptr);
}

void GameRendererImpl::AddLight(const wchar_t* name, D3DLIGHT9 const& init)
{
	lights_.emplace(name, init);
}

D3DLIGHT9* GameRendererImpl::GetLight(const wchar_t* name)
{
	auto const findIt = lights_.find(name);
	if (findIt != lights_.end())
	{
		return &findIt->second;
	}
	return nullptr;
}

void GameRendererImpl::RemoveLight(const wchar_t* name)
{
	lights_.erase(name);
}

HRESULT GameRendererImpl::GetEffect(const wchar_t* id, ID3DXEffect** effect)
{
	if (effect == nullptr)
	{
		return E_POINTER;
	}
	const auto findIt = effects_.find(id);
	if (findIt == effects_.end())
	{
		return E_INVALIDARG;
	}
	*effect = findIt->second.Get();
	findIt->second->AddRef();
	return S_OK;
}
void GameRendererImpl::DeferredRender()
{
	IDirect3DDevice9* const device = RenderManager::GetDevice();
	RenderTarget* const albedoRT	= RenderManager::GetRenderTarget(RENDER_TARGET_ALBEDO);
	RenderTarget* const normalRT	= RenderManager::GetRenderTarget(RENDER_TARGET_NORMAL);
	RenderTarget* const depthRT		= RenderManager::GetRenderTarget(RENDER_TARGET_DEPTH);
	RenderTarget* const specularRT	= RenderManager::GetRenderTarget(RENDER_TARGET_SPECULAR);
	ComPtr<IDirect3DSurface9> surface;

	surface = ComPtr<IDirect3DSurface9>{};
	albedoRT->GetSurface(&surface);
	device->SetRenderTarget(0, surface.Get() );

	surface = ComPtr<IDirect3DSurface9>{};
	normalRT->GetSurface(&surface);
	device->SetRenderTarget(1, surface.Get() );

	surface = ComPtr<IDirect3DSurface9>{};
	specularRT->GetSurface(&surface);
	device->SetRenderTarget(2, surface.Get() );

	surface = ComPtr<IDirect3DSurface9>{};
	depthRT->GetSurface(&surface);
	device->SetRenderTarget(3, surface.Get() );

	device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(0.f, 0.f, 0.f, 0.f), 1.f, 0);

	auto& list{ renderGroups_[RenderGroupID::Deferred] };
	std::vector<GameObject*> zSortedObjects;
	zSortedObjects.reserve(list.size());
	zSortedObjects.assign(list.begin(), list.end());
	std::sort(zSortedObjects.begin(), zSortedObjects.end(), PKH::ObjectManager::CompareZ);
	for (auto object : zSortedObjects)
	{
		object->Render();
	}
	UINT passCount{};
	deferredShader_->Begin(&passCount, 0);
	device->SetFVF(FVF);
	device->SetIndices(indexBuffer_.Get());
	device->SetStreamSource(0, vertexBuffer_.Get(), 0, sizeof(PPVertexFVF));
	DeferredLighting();
	DeferredCombine();

	deferredShader_->End();
}

void GameRendererImpl::DeferredLighting()
{
	IDirect3DDevice9* const device = RenderManager::GetDevice();
	D3DXVECTOR4 vCameraPosition{ Camera::main->GetPosition(), 1.f };
	Matrix	mInverseViewProj;
	RenderTarget* const albedoRT = RenderManager::GetRenderTarget(RENDER_TARGET_ALBEDO);
	RenderTarget* const normalRT = RenderManager::GetRenderTarget(RENDER_TARGET_NORMAL);
	RenderTarget* const depthRT = RenderManager::GetRenderTarget(RENDER_TARGET_DEPTH);
	RenderTarget* const specularRT = RenderManager::GetRenderTarget(RENDER_TARGET_SPECULAR);
	RenderTarget* const lightDiffuseMapRT = RenderManager::GetRenderTarget(LIGHT_DIFFUSE);
	RenderTarget* const lightSpecularMapRT = RenderManager::GetRenderTarget(LIGHT_SPECULAR);
	ComPtr<IDirect3DTexture9> texture{};
	ComPtr<IDirect3DSurface9> surface{};

	D3DXMatrixInverse(&mInverseViewProj, nullptr, &mViewProj);
	deferredShader_->SetMatrix(ID_CONST_INVERSE_VIEW_PROJ_MATRIX, &mInverseViewProj);


	texture = ComPtr<IDirect3DTexture9>{};
	normalRT->GetTexture(&texture);
	deferredShader_->SetTexture(ID_TEX_NORMAL_MAP, texture.Get());

	texture = ComPtr<IDirect3DTexture9>{};
	specularRT->GetTexture(&texture);
	deferredShader_->SetTexture(ID_TEX_SPECULAR_MAP, texture.Get());

	texture = ComPtr<IDirect3DTexture9>{};
	depthRT->GetTexture(&texture);
	deferredShader_->SetTexture(ID_TEX_DEPTH_MAP, texture.Get());

	surface = ComPtr<IDirect3DSurface9>{};
	lightDiffuseMapRT->GetSurface(&surface);
	device->SetRenderTarget(0, surface.Get());

	surface = ComPtr<IDirect3DSurface9>{};
	lightSpecularMapRT->GetSurface(&surface);
	device->SetRenderTarget(1, surface.Get());
	device->SetRenderTarget(2, nullptr);
	device->SetRenderTarget(3, nullptr);
	device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(0.f, 0.f, 0.f, 0.f), 1.f, 0);
	deferredShader_->SetVector("g_vCameraPosition", &vCameraPosition);
	for (auto const& pair : lights_)
	{
		int passNum = 0;
		const D3DLIGHT9& light = pair.second;
		switch (light.Type)
		{
		case D3DLIGHT_DIRECTIONAL:
			passNum = 1;
			{
				D3DXVECTOR4 vLightDir = D3DXVECTOR4(light.Direction, 1.f);
				deferredShader_->SetVector("g_vLightDirectionAndPower", &vLightDir);
				deferredShader_->SetVector("g_vLightAmbient", reinterpret_cast<D3DXVECTOR4 const*>(&light.Ambient));
				deferredShader_->SetVector("g_vLightDiffuse", reinterpret_cast<D3DXVECTOR4 const*>(&light.Diffuse));
			}
			break;
		}
		if (passNum == 0)continue;
		deferredShader_->BeginPass(passNum);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
		deferredShader_->EndPass();
	}
}

void GameRendererImpl::DeferredCombine()
{
	IDirect3DDevice9* const device	= RenderManager::GetDevice();
	RenderTarget* const albedoRT	= RenderManager::GetRenderTarget(RENDER_TARGET_ALBEDO);
	RenderTarget* const normalRT	= RenderManager::GetRenderTarget(RENDER_TARGET_NORMAL);
	RenderTarget* const depthRT		= RenderManager::GetRenderTarget(RENDER_TARGET_DEPTH);
	RenderTarget* const specularRT	= RenderManager::GetRenderTarget(RENDER_TARGET_SPECULAR);
	RenderTarget* const lightDiffuseMapRT	= RenderManager::GetRenderTarget(LIGHT_DIFFUSE);
	RenderTarget* const lightSpecularMapRT	= RenderManager::GetRenderTarget(LIGHT_SPECULAR);
	ComPtr<IDirect3DTexture9> texture{};
	ComPtr<IDirect3DSurface9> surface{};

	
	device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surface);
	device->SetRenderTarget(0, surface.Get());
	device->SetRenderTarget(1, nullptr);
	device->SetRenderTarget(2, nullptr);
	device->SetRenderTarget(3, nullptr);

	texture = ComPtr<IDirect3DTexture9>{};
	lightDiffuseMapRT->GetTexture(&texture);
	deferredShader_->SetTexture("g_shadeMap", texture.Get());

	texture = ComPtr<IDirect3DTexture9>{};
	lightSpecularMapRT->GetTexture(&texture);
	deferredShader_->SetTexture("g_specularMap", texture.Get());

	texture = ComPtr<IDirect3DTexture9>{};
	albedoRT->GetTexture(&texture);
	deferredShader_->SetTexture("g_albedoMap", texture.Get());

	texture = ComPtr<IDirect3DTexture9>{};
	depthRT->GetTexture(&texture);
	deferredShader_->SetTexture("g_depthMap", texture.Get());

	deferredShader_->BeginPass(0);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	deferredShader_->EndPass();
}

void GameRendererImpl::RenderUI()
{
	auto& list{ renderGroups_[RenderGroupID::UI] };
	std::vector<GameObject*> zSortedObjects;
	zSortedObjects.reserve(list.size());
	zSortedObjects.assign(list.begin(), list.end());
	std::sort(zSortedObjects.begin(), zSortedObjects.end(), PKH::ObjectManager::CompareZ);
	for (auto object : zSortedObjects)
	{
		if (object->isVisible == false) continue;
		object->Render();
	}
}

void GameRendererImpl::RenderHUD()
{
	auto& list{ renderGroups_[RenderGroupID::HUD] };
	std::vector<GameObject*> zSortedObjects;
	zSortedObjects.reserve(list.size());
	zSortedObjects.assign(list.begin(), list.end());
	std::sort(zSortedObjects.begin(), zSortedObjects.end(), PKH::ObjectManager::CompareZ);
	for (auto object : zSortedObjects)
	{
		if (object->isVisible == false) continue;
		object->Render();
	}
}

