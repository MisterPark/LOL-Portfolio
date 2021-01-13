#include "stdafx.h"
#include "OrderMinionMelee.h"

OrderMinionMelee::OrderMinionMelee()
{
	transform->scale = { 0.012f, 0.012f, 0.012f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"order_minion_melee");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
}

OrderMinionMelee::~OrderMinionMelee()
{
}
