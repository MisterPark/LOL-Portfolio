#include "stdafx.h"
#include "UIRenderer.h"
#include "RenderSystem.h"
#include "RenderManager.h"
int UIRenderer::uniqueZIndex = 0;

Engine::UIRenderer::UIRenderer(GameObject* owner)
	: Renderer{ owner, RendererType::UI }
{
	ui = (UI*)owner;
	ui->transform->zIndex = uniqueZIndex++;
	effect = RenderManager::LoadEffect(L"./HPBarEffect.fx");
}

IComponent* Engine::UIRenderer::Clone()
{
	return new UIRenderer(*this);
}

void Engine::UIRenderer::Render()
{
	if (visible == false) return;
	if (ui == nullptr) return;
	UINT passCount = 0;
	auto device = RenderManager::GetDevice();
	int screenW = MainGame::GetWidth();
	int screenH = MainGame::GetHeight();
	Matrix matWorld, matView, matProj, matOriginView, matOriginProj;
	Matrix matViewProj;
	D3DXVECTOR4 vecUVMax{ ui->uvRatio.x,ui->uvRatio.y, 0.f, 0.f};
	device->GetTransform(D3DTS_VIEW, &matOriginView);
	device->GetTransform(D3DTS_PROJECTION, &matOriginProj);
	D3DXMatrixOrthoLH(&matProj, (FLOAT)screenW, (FLOAT)screenH, 0.f, 1.f);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);
	matWorld = transform->GetWorldMatrix();
	matWorld._11 = (ui->size.x * matWorld._11) * 0.5f;
	matWorld._22 = (ui->size.y * matWorld._22) * 0.5f;
	matWorld._33 = 1.f;
	matWorld._41 = matWorld._41 - (screenW * 0.5f) + matWorld._11;
	matWorld._42 = -matWorld._42 + (screenH * 0.5f) - matWorld._22;
	matWorld._43 = 1.f;
	matViewProj = matView * matProj;
	effect->Begin(&passCount, 0);
	effect->SetMatrix("g_mViewProj", &matViewProj);
	effect->SetMatrix("g_mWorld", &matWorld);
	effect->SetTexture("g_texture", mesh->GetSubsetTexture(0));
	effect->SetVector("g_uvRatio",&vecUVMax);
	effect->BeginPass(0);

	mesh->RenderSubset(0);

	effect->EndPass();
	effect->End();
}

void Engine::UIRenderer::SetMesh(Engine::Mesh* mesh)
{
	this->mesh = mesh;
}

void Engine::UIRenderer::BringToTop()
{
	transform->zIndex = UIRenderer::uniqueZIndex;
}
