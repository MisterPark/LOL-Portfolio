#include "stdafx.h"
#include "ChaosMinionSiege.h"

ChaosMinionSiege::ChaosMinionSiege()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"chaos_minion_siege");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
}

ChaosMinionSiege::~ChaosMinionSiege()
{
}
