#include "stdafx.h"
#include "Krug.h"

Krug::Krug()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_krug");
	AddComponent(L"DynamicMesh", dmesh);
	dmesh->renderGroupID = RenderGroupID::Deferred;
	GameRenderer::Register(dmesh);
	anim->AttachToDynamicMesh(dmesh);

	anim->SetLoop((int)UnitState::IDLE1, true);
}

Krug::~Krug()
{
	DynamicMesh* dmesh = (DynamicMesh*)GetComponent(L"DynamicMesh");
	GameRenderer::Unregister(dmesh);
}
