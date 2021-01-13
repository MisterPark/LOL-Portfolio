#include "stdafx.h"
#include "OrderMinionCaster.h"

OrderMinionCaster::OrderMinionCaster()
{
	transform->scale = { 0.012f, 0.012f, 0.012f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"order_minion_caster");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
}

OrderMinionCaster::~OrderMinionCaster()
{
}
