#include "stdafx.h"
#include "FogOfWarObstacleRenderer.h"
#include "FogOfWarRenderSystem.h"
#include <wrl.h>
using namespace Microsoft::WRL;
Engine::FogOfWarObstacleRenderer::FogOfWarObstacleRenderer(GameObject* owner):
    Renderer{owner, RendererType::EarlyForward}
{
    heightFogOfWarRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_HEIGHT_FOG_OF_WAR);
    fogOfWarShader = RenderManager::LoadEffect(L"./fogOfWar_render.fx");
}

void Engine::FogOfWarObstacleRenderer::Render()
{
    IDirect3DDevice9* const device{ RenderManager::GetDevice() };
    ComPtr<IDirect3DSurface9> oldSurface;
    ComPtr<IDirect3DSurface9> oldDepthSurface;
    ComPtr<IDirect3DSurface9> heightSurface;
    ComPtr<IDirect3DSurface9> depth;

    heightFogOfWarRenderTarget->GetSurface(&heightSurface);
    FogOfWarRenderSystem::GetDepthBuffer(&depth);

    device->GetDepthStencilSurface(&oldDepthSurface);
    device->GetRenderTarget(0, &oldSurface);
    device->SetRenderTarget(0, heightSurface.Get());
    device->SetDepthStencilSurface(depth.Get());
    UINT passCount{};
    Matrix mWorld{ transform->GetWorldMatrix() };

    fogOfWarShader->Begin(&passCount, 0);
    fogOfWarShader->SetMatrix("g_mWorld", &mWorld);
    fogOfWarShader->BeginPass(0);
    int subsetCount = mesh->GetSubsetCount();
    for (int i = 0; i < subsetCount; ++i)
    {
        mesh->RenderSubset(i);
    }
    fogOfWarShader->EndPass();
    fogOfWarShader->End();
    device->SetRenderTarget(0, oldSurface.Get());
    device->SetDepthStencilSurface(oldDepthSurface.Get());
}

void Engine::FogOfWarObstacleRenderer::SetMesh(Engine::Mesh* mesh)
{
    this->mesh = mesh;
}

IComponent* Engine::FogOfWarObstacleRenderer::Clone()
{
    return nullptr;
}
