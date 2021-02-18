#include "stdafx.h"
#include "OrderMinionMelee.h"

OrderMinionMelee::OrderMinionMelee()
{
	transform->scale = { 0.012f, 0.012f, 0.012f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"order_minion_melee");
	AddComponent(L"DynamicMesh", dmesh);

	KST::SkinnedMeshRenderer* renderer = new KST::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->AttachToDynamicMesh(dmesh);
}

OrderMinionMelee::~OrderMinionMelee()
{
}
