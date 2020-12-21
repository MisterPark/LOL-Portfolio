#include "stdafx.h"
#include "Diana.h"

Diana::Diana()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"diana");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
}

Diana::~Diana()
{
}

void Diana::Initialize()
{
}

void Diana::Release()
{
}

void Diana::Update()
{
	Champion::Update();
}
