#include "stdafx.h"
#include "OrderMinionSuper.h"

OrderMinionSuper::OrderMinionSuper()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"order_minion_super");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
}

OrderMinionSuper::~OrderMinionSuper()
{
}
