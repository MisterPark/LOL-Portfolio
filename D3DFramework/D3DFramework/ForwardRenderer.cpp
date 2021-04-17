﻿#include "stdafx.h"
#include "ForwardRenderer.h"

Engine::ForwardRenderer::ForwardRenderer(GameObject* const owner, std::wstring const& path):
	Renderer(owner, RendererType::Forward)
{
	IDirect3DDevice9 * const device = RenderManager::GetDevice();
	effect = RenderManager::LoadEffect(path.c_str());
	effect->CloneEffect(device, &effect);
	mesh = nullptr;
	pass = 0;
}

Engine::ForwardRenderer::~ForwardRenderer()
{
	Safe_Release(&effect);
}

void Engine::ForwardRenderer::SetValue(const char* parameter, float value)
{
	effect->SetFloat(parameter, value);
}

void Engine::ForwardRenderer::SetValue(const char* parameter, Vector3 const& value)
{
	D3DXVECTOR4 copy{ value.x,value.y, value.z, 0.f };
	effect->SetVector(parameter, &copy);
}

void Engine::ForwardRenderer::SetValue(const char* parameter, D3DXVECTOR4 const& value)
{
	effect->SetVector(parameter, &value);
}

void Engine::ForwardRenderer::SetValue(const char* parameter, Matrix const& value)
{
	effect->SetMatrix(parameter, &value);
}

void Engine::ForwardRenderer::SetValue(const char* parameter, IDirect3DTexture9* const value)
{
	effect->SetTexture(parameter, value);
}

void Engine::ForwardRenderer::SetDiffuseTextureParam(const char* const parameter)
{
	diffuseTextureHandle = parameter;
}

void Engine::ForwardRenderer::SetPass(int pass)
{
	this->pass = pass;
}

void Engine::ForwardRenderer::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void Engine::ForwardRenderer::Render()
{
	if (visible == false) return;
	if (gameObject->visible == false) return;

	UINT passCount{};
	int const subsetCount = this->mesh->GetSubsetCount();
	Matrix mViewSpace = Camera::main->GetViewMatrix();
	Matrix mProjSpace = Camera::main->GetProjectionMatrix();
	Matrix mViewProj = mViewSpace * mProjSpace;
	Matrix mWorld = this->transform->GetWorldMatrix();

	effect->SetMatrix("g_mWorld", &mWorld);
	effect->SetMatrix("g_mViewProj", &mViewProj);
	effect->Begin(&passCount, 0);
	effect->BeginPass(pass);
	for (int i = 0; i < subsetCount; ++i)
	{
		IDirect3DTexture9* texture =  this->mesh->GetSubsetTexture(i);
		effect->SetTexture(diffuseTextureHandle.c_str(), texture);
		effect->CommitChanges();
		this->mesh->RenderSubset(i);
	}
	effect->EndPass();
	effect->End();
}

IComponent* Engine::ForwardRenderer::Clone()
{
	return nullptr;
}
