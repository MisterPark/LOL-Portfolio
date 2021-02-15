#include "stdafx.h"
#include "StandardMaterial.h"
#include "RenderSystem.h"
#include <wrl.h>
using namespace Microsoft::WRL;
KST::StandardMaterial::StandardMaterial()
{
	renderingShader = RenderManager::LoadEffect(L"./deferred_render.fx");
	deferredShader = RenderManager::LoadEffect(L"./deferred_shader.fx");

	albedoRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_ALBEDO);
	normalRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_NORMAL);
	sharpnessRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_SHARPNESS);
	depthRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_DEPTH);

	shaderType = ShaderType::Deferred;
	alphaTest = false;
	subsetIndex = -1;
	mesh = nullptr;
	threshold = 0.f;
}

void KST::StandardMaterial::Render()
{
	RenderShadowMap();
	RenderGBuffer();
}

void KST::StandardMaterial::SetSubset(int index)
{
	this->subsetIndex = index;
}

void KST::StandardMaterial::SetMesh(PKH::Mesh* mesh)
{
	this->mesh = mesh;
}

void KST::StandardMaterial::EnableAlphaTest(float threshold)
{
	alphaTest = true;
	this->threshold = threshold;
}

void KST::StandardMaterial::DisableAlphaTest()
{
	alphaTest = false;
}

void KST::StandardMaterial::RenderShadowMap()
{

}

void KST::StandardMaterial::RenderGBuffer()
{
	UINT passCount = 0;
	Matrix mViewProj;
	Matrix mViewSpace = Camera::main->GetViewMatrix();
	Matrix mProjSpace = Camera::main->GetProjectionMatrix();
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

	mViewProj = mViewSpace * mProjSpace;
	renderingShader->SetMatrix("g_mViewSpace", &mViewSpace);
	renderingShader->SetMatrix("g_mProjSpace", &mProjSpace);
	renderingShader->SetMatrix("g_mViewProj", &mViewProj);
	renderingShader->Begin(&passCount, 0);
	if (alphaTest)
	{
		renderingShader->BeginPass(0);
	}
	else
	{
		renderingShader->SetFloat("g_alphaThreshold", 0.4f);
		renderingShader->BeginPass(1);
	}
	mesh->RenderSubset(subsetIndex);
	renderingShader->EndPass();
	renderingShader->End();
}
