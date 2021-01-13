#include "stdafx.h"
#include "ChaosMinionSuper.h"

ChaosMinionSuper::ChaosMinionSuper()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"chaos_minion_super");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
}

ChaosMinionSuper::~ChaosMinionSuper()
{
}
