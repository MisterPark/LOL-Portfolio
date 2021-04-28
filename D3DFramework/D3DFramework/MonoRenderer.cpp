#include "stdafx.h"
#include "MonoRenderer.h"
#include <wrl.h>
using namespace Microsoft::WRL;
namespace Engine
{
	MonoRenderer::MonoRenderer(GameObject* owner) :
		Renderer(owner, RendererType::PostProcessEffect)
	{
		monoShader = RenderManager::LoadEffect(L"./mono.fx");
	}

	void MonoRenderer::Render()
	{
		if (!enable) return;

		UINT passCount{};
		ComPtr<IDirect3DTexture9> screenTexture;
		ComPtr<IDirect3DSurface9> backbuffer;
		IDirect3DDevice9* device = RenderManager::GetDevice();
		device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
		RenderTarget* screen = RenderManager::GetRenderTarget(RENDER_TARGET_SCREEN);

		screen->GetTexture(&screenTexture);
		monoShader->SetTexture("g_texture", screenTexture.Get());
		device->SetRenderTarget(0, backbuffer.Get());
		monoShader->Begin(&passCount, 0);

		if (mesh == nullptr)
		{
			monoShader->BeginPass(0);
			RenderSystem::SetupPostProcessing();
			RenderSystem::ExecutePostProcessing();
		}
		else
		{
			Matrix mViewSpace = Camera::main->GetViewMatrix();
			Matrix mProjSpace = Camera::main->GetProjectionMatrix();
			Matrix mViewProj = mViewSpace * mProjSpace;
			Matrix mWorld = this->transform->GetWorldMatrix();
			monoShader->SetMatrix("g_mWorld", &mWorld);
			monoShader->SetMatrix("g_mViewProj", &mViewProj);
			int subsetCount = mesh->GetSubsetCount();
			monoShader->BeginPass(1);
			for (int i = 0; i < subsetCount; ++i)
			{
				mesh->RenderSubset(i);
			}
		}

		monoShader->EndPass();
		monoShader->End();
	}

	void MonoRenderer::SetMesh(Mesh* mesh)
	{
		this->mesh = mesh;
	}


	IComponent* Engine::MonoRenderer::Clone()
	{
		return nullptr;
	}

}
