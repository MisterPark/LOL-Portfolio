#include "stdafx.h"
#include "IRenderComponent.h"

void UIRenderComponent::Render()
{
	if (this->gameObject != nullptr)
	{
		auto device = RenderManager::GetDevice();
		int screenW = MainGame::GetWidth();
		int screenH = MainGame::GetHeight();
		Matrix matWorld, matView, matProj, matOriginView, matOriginProj;

		device->GetTransform(D3DTS_VIEW, &matOriginView);
		device->GetTransform(D3DTS_PROJECTION, &matOriginProj);

		D3DXMatrixOrthoLH(&matProj, (FLOAT)screenW, (FLOAT)screenH, 0.f, 1.f);
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matView);

		//matWorld._11 = transform->scale.x;
		//matWorld._22 = transform->scale.y;
		//matWorld._33 = 1.f;
		//matWorld._41 = transform->position.x - (screenW * 0.5f) + transform->scale.x;
		//matWorld._42 = -transform->position.y + (screenH * 0.5f) - transform->scale.y;

		matWorld = transform->GetWorldMatrix();
		matWorld._11 = matWorld._11 * 0.5f;
		matWorld._22 = matWorld._22 * 0.5f;
		matWorld._33 = 1.f;
		matWorld._41 = matWorld._41 - (screenW * 0.5f) + matWorld._11;
		matWorld._42 = -matWorld._42 + (screenH * 0.5f) - matWorld._22;
		//matWorld._43 = 1.f;

		device->SetTransform(D3DTS_WORLD, &matWorld);
		device->SetTransform(D3DTS_VIEW, &matView);
		device->SetTransform(D3DTS_PROJECTION, &matProj);

		this->gameObject->Render();

		device->SetTransform(D3DTS_VIEW, &matOriginView);
		device->SetTransform(D3DTS_PROJECTION, &matOriginProj);

	}
}
