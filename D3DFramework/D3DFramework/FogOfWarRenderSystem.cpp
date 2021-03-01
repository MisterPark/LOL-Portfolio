#include "stdafx.h"
#include "FogOfWarRenderSystem.h"
#include "FogOfWarObstacleRenderer.h"
#include "Wall.h"
#include <wrl.h>
using namespace Microsoft::WRL;
namespace Engine
{
	std::list<FogOfWarRenderSystem::FogSight> sights;
	static RenderTarget* fogOfWarRenderTarget;
	static RenderTarget* heightFogOfWarRenderTarget;
	ID3DXEffect* fogOfWarShader;
	Matrix mapSpace;
	constexpr float EDGE_LENGTH = 110.f;
	ComPtr<IDirect3DSurface9> depthBuffer;
	void FogOfWarRenderSystem::Initialize()
	{
		IDirect3DDevice9* const device = RenderManager::GetDevice();
		//device->CreateDepthStencilSurface(256, 256, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, false, &depthBuffer, nullptr);
		fogOfWarRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_FOG_OF_WAR);
		RenderManager::CreateRenderTarget(RENDER_TARGET_HEIGHT_FOG_OF_WAR, 1024, 1024, D3DFMT_R16F);
		heightFogOfWarRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_HEIGHT_FOG_OF_WAR);
		fogOfWarShader = RenderManager::LoadEffect(L"./fogOfWar_render.fx");
		D3DXMatrixScaling(&mapSpace, 2.f / EDGE_LENGTH, 1.f, 2.f / EDGE_LENGTH);
		Vector3 vEye;
		Vector3 vUp;
		Vector3 vAt;
		vEye = Vector3{ 0.f, 2000.f, 0.f };
		vAt = Vector3{ 0.f, 0.f, 0.f };
		vUp = Vector3{ 0.f, 0.f, 1.f };
		Matrix mProj;
		Matrix mView;
		Matrix mViewProj;
		D3DXMatrixLookAtLH(&mView, &vEye, &vAt, &vUp);
		D3DXMatrixOrthoLH(&mProj, EDGE_LENGTH, EDGE_LENGTH, 0.f, 3000.f);
		mViewProj = mView * mProj;
		fogOfWarShader->SetMatrix("g_mMapSpace", &mViewProj);

	}
	void FogOfWarRenderSystem::Destory()
	{
		sights.clear();
	}

	void FogOfWarRenderSystem::Begin()
	{
		IDirect3DDevice9* device = RenderManager::GetDevice();
		ComPtr<IDirect3DSurface9> fogOfWarSurface;
		ComPtr<IDirect3DSurface9> heightFogOfWarSurface;
		ComPtr<IDirect3DSurface9> oldSurface;
		ComPtr<IDirect3DSurface9> oldDepth;
		fogOfWarRenderTarget->GetSurface(&fogOfWarSurface);
		heightFogOfWarRenderTarget->GetSurface(&heightFogOfWarSurface);
		device->GetDepthStencilSurface(&oldDepth);
		device->GetRenderTarget(0, &oldSurface);
		device->SetRenderTarget(0, fogOfWarSurface.Get());
		device->SetRenderTarget(1, nullptr);
		device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(0.f, 0.f, 0.f, 1.f), 1.f, 0);
		device->SetRenderTarget(0, heightFogOfWarSurface.Get());
		device->SetRenderTarget(1, nullptr);
		device->SetRenderTarget(2, nullptr);
		device->SetRenderTarget(3, nullptr);
		//device->SetDepthStencilSurface(depthBuffer.Get());
		device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(0.f, 0.f, 0.f, 1.f), 1.f, 0);
		device->SetRenderTarget(0, oldSurface.Get());
		device->SetDepthStencilSurface(oldSurface.Get());
	}

	void FogOfWarRenderSystem::End()
	{
		UINT passCount{};

		IDirect3DDevice9* const device = RenderManager::GetDevice();
		IDirect3DSurface9* fogOfWarSurface;
		IDirect3DSurface9* oldSurface;
		IDirect3DTexture9* fogOfWarTexture;
		IDirect3DTexture9* heightMapTexture;
		
		fogOfWarRenderTarget->GetSurface(&fogOfWarSurface);
		fogOfWarRenderTarget->GetTexture(&fogOfWarTexture);
		heightFogOfWarRenderTarget->GetTexture(&heightMapTexture);
		device->GetRenderTarget(0, &oldSurface);
		device->SetRenderTarget(0, fogOfWarSurface);

		device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(0.f, 0.f, 0.f, 1.f), 1.f, 0);

		fogOfWarShader->Begin(&passCount, 0);
		fogOfWarShader->SetTexture("g_heightMap", heightMapTexture);

		RenderSystem::SetupPostProcessing();

		fogOfWarShader->BeginPass(1);

		for (auto const& sight : sights)
		{
			float radius1 = sight.radius1 / (EDGE_LENGTH * 0.5f);
			float radius2 = sight.radius2 / (EDGE_LENGTH * 0.5f);
			D3DXVECTOR4 vPosition{};
			D3DXVec3TransformCoord(
				reinterpret_cast<D3DXVECTOR3*>(&vPosition),
				reinterpret_cast<D3DXVECTOR3 const*>(&sight.position),
				&mapSpace
			);
			fogOfWarShader->SetFloat("g_sightRadius", radius1);
			fogOfWarShader->SetFloat("g_sightRadius2", radius2);
			fogOfWarShader->SetVector("g_vSightPosition", &vPosition);
			fogOfWarShader->CommitChanges();
			RenderSystem::ExecutePostProcessing();
		}

		fogOfWarShader->EndPass();
		device->SetRenderTarget(0, oldSurface);
		fogOfWarShader->BeginPass(2);

		//RenderSystem::ExecutePostProcessing();

		fogOfWarShader->EndPass();
		fogOfWarShader->End();
		fogOfWarShader->SetTexture("g_heightMap", nullptr);

		//
		Safe_Release(&fogOfWarTexture);
		Safe_Release(&oldSurface);
		Safe_Release(&fogOfWarSurface);
		Safe_Release(&heightMapTexture);
		
		sights.clear();
	}

	void FogOfWarRenderSystem::GetMapSpace(Matrix* out)
	{
		*out = mapSpace;
	}

	void FogOfWarRenderSystem::AddSight(FogSight const& fogSight)
	{
		sights.push_back(fogSight);
	}
	void FogOfWarRenderSystem::GetDepthBuffer(IDirect3DSurface9** surface)
	{
		//*surface = depthBuffer.Get();
		//depthBuffer->AddRef();
	}
}
