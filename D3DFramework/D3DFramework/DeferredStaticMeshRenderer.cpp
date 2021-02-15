#include "stdafx.h"
#include "RenderTarget.h"
#include "DeferredStaticMeshRenderer.h"
#include "RenderSystem.h"
#include <wrl.h>
using namespace Microsoft::WRL;
namespace KST
{

	DeferredStaticMeshRenderer::DeferredStaticMeshRenderer(PKH::GameObject* owner) :
		Renderer{ owner, RendererType::Deferred }
	{
		alphaTest = false;
		albedoRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_ALBEDO);
		normalRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_NORMAL);
		sharpnessRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_SHARPNESS);
		depthRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_DEPTH);
		renderingShader = RenderManager::LoadEffect(L"./deferred_render.fx");

	}

	void DeferredStaticMeshRenderer::EnableAlphaTest(float threshold)
	{
		alphaTest = true;
		this->threshold = threshold;
	}

	void DeferredStaticMeshRenderer::DisableAlphaTest()
	{
		alphaTest = false;
	}

	bool DeferredStaticMeshRenderer::IsAlphaTest()
	{
		return alphaTest;
	}

	void DeferredStaticMeshRenderer::SetMesh(PKH::Mesh* mesh)
	{
		this->mesh = mesh;
	}

	void DeferredStaticMeshRenderer::Render()
	{
		RenderShadowMap();
		RenderGBuffer();
	}
	void DeferredStaticMeshRenderer::RenderShadowMap()
	{
		//TODO: 이제 셰도우의 투영행렬를 받아서 셰도우 맵에 메시를 렌더링해야 한다.
	}
	void DeferredStaticMeshRenderer::RenderGBuffer()
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
		//device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(0.f, 0.f, 0.f, 0.f), 1.f, 0);
		UINT passCount = 0;
		UINT passNum = 0;

		Matrix mViewSpace = Camera::main->GetViewMatrix();
		Matrix mProjSpace = Camera::main->GetProjectionMatrix();
		Matrix mViewProj = mViewSpace * mProjSpace;
		renderingShader->SetMatrix("g_mViewSpace", &mViewSpace);
		renderingShader->SetMatrix("g_mProjSpace", &mProjSpace);
		renderingShader->SetMatrix("g_mViewProj", &mViewProj);
		renderingShader->SetMatrix("g_mWorld", &transform->world);

		if (alphaTest)
		{
			passNum = 1;
			renderingShader->SetFloat("g_alphaThreshold", threshold);
		}
		renderingShader->Begin(&passCount, 0);
		renderingShader->BeginPass(passNum);
		int subsetCount = mesh->GetSubsetCount();
		for (int i = 0; i < subsetCount; ++i)
		{
			IDirect3DTexture9* texture = mesh->GetSubsetTexture(i);
			renderingShader->SetTexture("g_diffuseTexture", texture);
			renderingShader->CommitChanges();
			mesh->RenderSubset(i);
		}
		renderingShader->EndPass();
		renderingShader->End();

	}
}

