#include "stdafx.h"
#include "OrderMinionSiege.h"

OrderMinionSiege::OrderMinionSiege()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"order_minion_siege");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
}

OrderMinionSiege::~OrderMinionSiege()
{
}
