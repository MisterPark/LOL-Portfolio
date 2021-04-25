#include "stdafx.h"
#include "DistortionRenderer.h"
#include <wrl.h>
using namespace Microsoft::WRL;
namespace Engine
{
	DistortionRenderer::DistortionRenderer(GameObject* owner):
		Renderer(owner, RendererType::PostProcessEffect)
	{
		distortionShader = RenderManager::LoadEffect(L"./distortion.fx");
		RenderManager::LoadTexture(L"Resource/texture/", L"noise1.png");
		noiseTexture = RenderManager::GetTexture(L"noise1");
		normalRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_NORMAL);
		//opacity = 0.5f;
		opacity = 1.0f;
		mesh = nullptr;
	}

	void DistortionRenderer::Render()
	{
		UINT passCount{};
		ComPtr<IDirect3DTexture9> screenTexture;
		ComPtr<IDirect3DSurface9> backbuffer;
		IDirect3DDevice9* device = RenderManager::GetDevice();
		device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
		RenderTarget* screen = RenderManager::GetRenderTarget(RENDER_TARGET_SCREEN);

		screen->GetTexture(&screenTexture);
		distortionShader->SetTexture("g_texture", screenTexture.Get());
		distortionShader->SetTexture("g_noiseTexture", noiseTexture->pTexture);
		distortionShader->SetFloat("g_opacity", opacity);
		device->SetRenderTarget(0, backbuffer.Get());
		distortionShader->Begin(&passCount, 0);
		//메시가 지정되어 있지 않으면 전체 화면에 뿌려버린다.
		if (mesh == nullptr)
		{
			distortionShader->BeginPass(0);
			RenderSystem::SetupPostProcessing();
			RenderSystem::ExecutePostProcessing();
		}
		else
		{
			ComPtr<IDirect3DTexture9> normalDepthMapTex;
			normalRenderTarget->GetTexture(&normalDepthMapTex);
			Matrix mViewSpace = Camera::main->GetViewMatrix();
			Matrix mProjSpace = Camera::main->GetProjectionMatrix();
			Matrix mViewProj = mViewSpace * mProjSpace;
			Matrix mWorld = this->transform->GetWorldMatrix();
			distortionShader->SetMatrix("g_mWorld", &mWorld);
			distortionShader->SetMatrix("g_mViewProj", &mViewProj);
			distortionShader->SetTexture("g_normalDepthMap", normalDepthMapTex.Get());
			int subsetCount = mesh->GetSubsetCount();
			distortionShader->BeginPass(1);
			for (int i = 0; i < subsetCount; ++i)
			{
				mesh->RenderSubset(i);
			}
		}
		distortionShader->EndPass();
		distortionShader->End();
	}

	void DistortionRenderer::SetMesh(Mesh* mesh)
	{
		this->mesh = mesh;
	}

	void DistortionRenderer::SetNoiseTexture(Texture* _tex)
	{
		noiseTexture = _tex;
	}

	void DistortionRenderer::SetOpacity(float op)
	{
		opacity = op;
	}

	IComponent* Engine::DistortionRenderer::Clone()
	{
		return nullptr;
	}

}
