﻿#include "stdafx.h"
#include "FogOfWarRenderSystem.h"
#include "FogOfWarObstacleRenderer.h"
#include "Wall.h"
#include <wrl.h>
#include <array>
using namespace Microsoft::WRL;
namespace Engine
{
	std::list<FogOfWarRenderSystem::FogSight> sights;
	static RenderTarget* fogOfWarRenderTarget;
	static RenderTarget* blurRenderTarget1;
	static RenderTarget* blurRenderTarget2;
	static RenderTarget* heightFogOfWarRenderTarget;
	ID3DXEffect* fogOfWarShader;
	ID3DXEffect* blurShader;
	Matrix mapSpace;
	constexpr float EDGE_LENGTH = 98.f;
	ComPtr<IDirect3DSurface9> depthBuffer;
	std::array<std::array<bool, 256>, 256> sightMap;
	ComPtr<IDirect3DTexture9> fogCopyTexture;
	void FogOfWarRenderSystem::Initialize()
	{
		IDirect3DDevice9* const device = RenderManager::GetDevice();
		device->CreateDepthStencilSurface(2048, 2048, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, false, &depthBuffer, nullptr);
		fogOfWarRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_FOG_OF_WAR);
		RenderManager::CreateRenderTarget(RENDER_TARGET_HEIGHT_FOG_OF_WAR, 2048, 2048, D3DFMT_R16F);
		RenderManager::CreateRenderTarget(L"FogOfWarRenderSystem_Blur1", 1024, 1024, D3DFMT_R16F);
		RenderManager::CreateRenderTarget(L"FogOfWarRenderSystem_Blur2", 1024, 1024, D3DFMT_R16F);
		blurRenderTarget1 = RenderManager::GetRenderTarget(L"FogOfWarRenderSystem_Blur1");
		blurRenderTarget2 = RenderManager::GetRenderTarget(L"FogOfWarRenderSystem_Blur2");
		heightFogOfWarRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_HEIGHT_FOG_OF_WAR);
		fogOfWarShader = RenderManager::LoadEffect(L"./fogOfWar_render.fx");
		blurShader = RenderManager::LoadEffect(L"./blur.fx");
		Vector3 vEye;
		Vector3 vUp;
		Vector3 vAt;
		vEye = Vector3{ 3.f, 2000.f, -4.f };
		vAt = Vector3{ -3.f, 0.f, 4.f };
		vUp = Vector3{ 0.f, 0.f, -1.f };
		Matrix mProj;
		Matrix mView;
		Matrix mViewProj;
		D3DXMatrixLookAtLH(&mView, &vEye, &vAt, &vUp);
		D3DXMatrixOrthoLH(&mProj, EDGE_LENGTH, EDGE_LENGTH, 0.f, 3000.f);
		mViewProj = mView * mProj;
		fogOfWarShader->SetMatrix("g_mMapSpace", &mViewProj);
		mapSpace = mViewProj;

		device->CreateTexture(256, 256, 1, 0, D3DFMT_R32F, D3DPOOL_SYSTEMMEM, &fogCopyTexture, nullptr);
	}
	void FogOfWarRenderSystem::Destory()
	{
		sights.clear();
	}

	void FogOfWarRenderSystem::Begin()
	{
		HRESULT hr{};
		IDirect3DDevice9* device = RenderManager::GetDevice();
		ComPtr<IDirect3DSurface9> fogOfWarSurface;
		ComPtr<IDirect3DSurface9> heightFogOfWarSurface;
		ComPtr<IDirect3DSurface9> oldSurface;
		ComPtr<IDirect3DSurface9> oldDepth;
		fogOfWarRenderTarget->GetSurface(&fogOfWarSurface);
		heightFogOfWarRenderTarget->GetSurface(&heightFogOfWarSurface);
		device->GetDepthStencilSurface(&oldDepth);
		hr= device->GetRenderTarget(0, &oldSurface);
		hr = device->SetRenderTarget(0, fogOfWarSurface.Get());
		hr = device->SetRenderTarget(1, nullptr);
		hr = device->SetRenderTarget(2, nullptr);
		hr = device->SetRenderTarget(3, nullptr);

		hr = device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(0.f, 0.f, 0.f, 1.f), 1.f, 0);
		hr = device->SetRenderTarget(0, heightFogOfWarSurface.Get());
		hr = device->SetRenderTarget(1, nullptr);
		hr = device->SetRenderTarget(2, nullptr);
		hr = device->SetRenderTarget(3, nullptr);
		hr = device->SetDepthStencilSurface(depthBuffer.Get());
		hr = device->Clear(0, nullptr, D3DCLEAR_TARGET |  D3DCLEAR_ZBUFFER |D3DCLEAR_STENCIL, D3DCOLOR_COLORVALUE(0.f, 0.f, 0.f, 1.f), 1.f, 0);
		hr = device->SetRenderTarget(0, oldSurface.Get());
		hr = device->SetDepthStencilSurface(oldDepth.Get());
		
	}

	void FogOfWarRenderSystem::End()
	{
		UINT passCount{};
		HRESULT hr{};

		IDirect3DDevice9* const device = RenderManager::GetDevice();
		IDirect3DSurface9* fogOfWarSurface;
		IDirect3DSurface9* oldSurface;
		IDirect3DSurface9* blurSurface1;
		IDirect3DSurface9* blurSurface2;
		IDirect3DTexture9* fogOfWarTexture;
		IDirect3DTexture9* heightMapTexture;
		IDirect3DTexture9* blurTexture1;

		fogOfWarRenderTarget->GetSurface(&fogOfWarSurface);
		fogOfWarRenderTarget->GetTexture(&fogOfWarTexture);
		heightFogOfWarRenderTarget->GetTexture(&heightMapTexture);


		device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(0.f, 0.f, 0.f, 1.f), 1.f, 0);

		fogOfWarShader->Begin(&passCount, 0);
		fogOfWarShader->SetTexture("g_heightMap", heightMapTexture);

		RenderSystem::SetupPostProcessing();

		fogOfWarShader->BeginPass(1);
		hr = device->GetRenderTarget(0, &oldSurface);
		hr = device->SetRenderTarget(0, fogOfWarSurface);
		hr = device->SetRenderTarget(1, nullptr);
		hr = device->SetRenderTarget(2, nullptr);
		hr = device->SetRenderTarget(3, nullptr);
		for (auto const& sight : sights)
		{
			float radius1 = sight.radius1 / (EDGE_LENGTH * 0.5f);
			float radius2 = sight.radius2 / (EDGE_LENGTH * 0.5f);
			D3DXVECTOR4 vPosition{ sight.position.x,sight.position.y,sight.position.z, 0.f };

			D3DXVec3TransformCoord(
				reinterpret_cast<D3DXVECTOR3*>(&vPosition),
				reinterpret_cast<D3DXVECTOR3 const*>(&vPosition),
				&mapSpace
			);
			vPosition.x *= 256.f;
			vPosition.y *= 256.f;
			vPosition.x = round(vPosition.x)/ 256.f;
			vPosition.y = round(vPosition.y)/ 256.f;
			fogOfWarShader->SetFloat("g_sightRadius", radius1);
			fogOfWarShader->SetFloat("g_sightRadius2", radius2);
			fogOfWarShader->SetVector("g_vSightPosition", &vPosition);
			fogOfWarShader->CommitChanges();
			RenderSystem::ExecutePostProcessing();
		}

		fogOfWarShader->EndPass();
		
		fogOfWarShader->End();
		fogOfWarShader->SetTexture("g_heightMap", nullptr);

		blurRenderTarget1->GetSurface(&blurSurface1);
		hr = device->SetRenderTarget(0, blurSurface1);
		//blur먹이자
		D3DXVECTOR4 pixels[13]{
			{ -6, -6 ,0,0 },
			{ -5, -5 ,0,0 },
			{ -4, -4 ,0,0 },
			{ -3, -3 ,0,0 },
			{ -2, -2 ,0,0 },
			{ -1, -1 ,0,0 },
			{  0,  0 ,0,0 },
			{  1,  1 ,0,0 },
			{  2,  2 ,0,0 },
			{  3,  3 ,0,0 },
			{  4,  4 ,0,0 },
			{  5,  5 ,0,0 },
			{  6,  6 ,0,0 },
		};
		D3DXVECTOR4 texels[13] = { };
		for (int i = 0; i < 13; ++i)
		{
			texels[i] = pixels[i] / 256.f;
			texels[i].y = 0.f;
		}
		blurShader->SetVectorArray("TexelKernel", texels, 13);
		blurShader->SetTexture("g_texture", fogOfWarTexture);
		
		blurShader->Begin(&passCount, 0);
		blurShader->BeginPass(0);
		RenderSystem::ExecutePostProcessing();
		blurRenderTarget1->GetTexture(&blurTexture1);
		blurRenderTarget2->GetSurface(&blurSurface2);
		hr = device->SetRenderTarget(0, blurSurface2);

		for (int i = 0; i < 13; ++i)
		{
			texels[i] = pixels[i] / 1024.f;
			texels[i].x = 0.f;
		}
		blurShader->SetVectorArray("TexelKernel", texels, 13);
		blurShader->SetTexture("g_texture", blurTexture1);
		blurShader->CommitChanges();
		RenderSystem::ExecutePostProcessing();
		blurShader->EndPass();

		blurShader->End();
		device->SetRenderTarget(0, oldSurface);
		//
		Safe_Release(&fogOfWarTexture);
		Safe_Release(&oldSurface);

		Safe_Release(&heightMapTexture);
		Safe_Release(&blurSurface1);
		Safe_Release(&blurSurface2);
		Safe_Release(&blurTexture1);
		sights.clear();

		D3DLOCKED_RECT rc{};
		ComPtr<IDirect3DSurface9> fogCopySurface;
		fogCopyTexture->GetSurfaceLevel(0, &fogCopySurface);

		hr = device->GetRenderTargetData(fogOfWarSurface, fogCopySurface.Get());
		hr = fogCopyTexture->LockRect(0, &rc, nullptr, D3DLOCK_READONLY);
		auto const& fogs = *(std::array<std::array<float, 256>, 256> const*) rc.pBits;
		for (int row = 0; row < 256; ++row)
		{
			for (int cols = 0; cols < 256; ++cols)
			{
				float level = fogs[row][cols];
				sightMap[row][cols] = level >= 0.1f ? true : false;
			}
		}
		fogCopyTexture->UnlockRect(0);
		Safe_Release(&fogOfWarSurface);
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
		*surface = depthBuffer.Get();
		depthBuffer->AddRef();
	}
	bool FogOfWarRenderSystem::IsInSight(Vector3 const& pos)
	{
		Vector3 vPosition;
		D3DXVec3TransformCoord(
			&vPosition,
			&pos,
			&mapSpace
		);
		vPosition.x *= 256.f;
		vPosition.y *= 256.f;
		vPosition.x = round(vPosition.x) / 256.f;
		vPosition.y = round(vPosition.y) / 256.f;

		vPosition.y *= -1.f;
		Vector3 delta{ 0.5f, 0.5f, 0.f };
		vPosition =  vPosition * 0.5f + delta;
		vPosition.x *= 256.f;
		vPosition.y *= 256.f;

		if (!(((int)(vPosition.x) >= 0) && ((int)(vPosition.x) < 256))) false;
		if (!(((int)(vPosition.y) >= 0) && ((int)(vPosition.y) < 256))) false;

		return sightMap[(int)vPosition.y][(int)vPosition.x];
	}
}
