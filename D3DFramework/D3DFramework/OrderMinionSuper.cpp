#include "stdafx.h"
#include "OrderMinionSuper.h"

OrderMinionSuper::OrderMinionSuper()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"order_minion_super");
	AddComponent(L"DynamicMesh", dmesh);

	KST::SkinnedMeshRenderer* renderer = new KST::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->AttachToDynamicMesh(dmesh);
}

OrderMinionSuper::~OrderMinionSuper()
{
}
