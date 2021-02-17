#include "stdafx.h"
#include "UIRenderer.h"
#include "RenderSystem.h"

KST::UIRenderer::UIRenderer(GameObject* owner)
	: Renderer{ owner, RendererType::UI }
{
	ui = (UI*)owner;
}

IComponent* KST::UIRenderer::Clone()
{
	return new UIRenderer(*this);
}

void KST::UIRenderer::Render()
{
	if (visible == false) return;
	if (ui == nullptr) return;

	auto device = RenderManager::GetDevice();
	int screenW = MainGame::GetWidth();
	int screenH = MainGame::GetHeight();
	Matrix matWorld, matView, matProj, matOriginView, matOriginProj;

	device->GetTransform(D3DTS_VIEW, &matOriginView);
	device->GetTransform(D3DTS_PROJECTION, &matOriginProj);
	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	D3DXMatrixOrthoLH(&matProj, (FLOAT)screenW, (FLOAT)screenH, 0.f, 1.f);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	//matWorld._11 = transform->scale.x;
	//matWorld._22 = transform->scale.y;
	//matWorld._33 = 1.f;
	//matWorld._41 = transform->position.x - (screenW * 0.5f) + transform->scale.x;
	//matWorld._42 = -transform->position.y + (screenH * 0.5f) - transform->scale.y;

	matWorld = transform->GetWorldMatrix();
	matWorld._11 = (ui->size.x * matWorld._11) * 0.5f;
	matWorld._22 = (ui->size.y * matWorld._22) * 0.5f;
	matWorld._33 = 1.f;
	matWorld._41 =  matWorld._41 - (screenW * 0.5f) + matWorld._11;
	matWorld._42 =  -matWorld._42 + (screenH * 0.5f) - matWorld._22;
	matWorld._43 = 1.f;

	device->SetTransform(D3DTS_WORLD, &matWorld);
	device->SetTransform(D3DTS_VIEW, &matView);
	device->SetTransform(D3DTS_PROJECTION, &matProj);

	device->SetTexture(0, mesh->GetSubsetTexture(0));
	mesh->RenderSubset(0);

	device->SetTransform(D3DTS_VIEW, &matOriginView);
	device->SetTransform(D3DTS_PROJECTION, &matOriginProj);
	device->SetRenderState(D3DRS_ZENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

}

void KST::UIRenderer::SetMesh(PKH::Mesh* mesh)
{
	this->mesh = mesh;
}
