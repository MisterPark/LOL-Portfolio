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

	RenderManager::LoadTexture(L"Resource/texture/", L"timer.png");
	timerGradientTex = RenderManager::GetTexture(L"timer");
	timerRatio = 1.f;
}

IComponent* Engine::UIRenderer::Clone()
{
	return new UIRenderer(*this);
}

void Engine::UIRenderer::Render()
{
	if (gameObject->visible == false) return;
	if (visible == false) return;
	if (ui == nullptr) return;

	UINT passCount = 0;
	auto device = RenderManager::GetDevice();
	int screenW = MainGame::GetWidth();
	int screenH = MainGame::GetHeight();
	Matrix matWorld, matView, matProj, matOriginView, matOriginProj;
	Matrix matViewProj;
	D3DXVECTOR4 vecUVStart{ ui->uvRatioStart.x, ui->uvRatioStart.y, 0.f, 0.f};
	D3DXVECTOR4 vecUVEnd  { ui->uvRatioEnd.x,   ui->uvRatioEnd.y, 0.f, 0.f};
	D3DXVECTOR4 timerColor{ ui->timerColor.r / 256, ui->timerColor.g / 256, ui->timerColor.b / 256, ui->timerColor.a / 256 };
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
	effect->SetVector("g_uvRatioStart",&vecUVStart);
	effect->SetVector("g_uvRatioEnd",&vecUVEnd);
	effect->SetTexture("g_timerMap", timerGradientTex->pTexture);
	effect->SetFloat("g_timerThresHold", timerRatio);
	effect->SetVector("g_timerColor", &timerColor);
	effect->SetBool("g_grayscale", ui->grayscale);
	effect->BeginPass(0);

	mesh->RenderSubset(0);

	effect->EndPass();
	effect->End();
}

void Engine::UIRenderer::SetMesh(Engine::Mesh* mesh)
{
	this->mesh = mesh;
}

void Engine::UIRenderer::SetTimerRatio(float ratio)
{
	this->timerRatio = ratio;
}

void Engine::UIRenderer::BringToTop()
{
	transform->zIndex = UIRenderer::uniqueZIndex;
}
