#include "stdafx.h"
#include "ChaosMinionMelee.h"

ChaosMinionMelee::ChaosMinionMelee()
{
	transform->scale = { 0.012f, 0.012f, 0.012f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"chaos_minion_melee");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
}

ChaosMinionMelee::~ChaosMinionMelee()
{
}
