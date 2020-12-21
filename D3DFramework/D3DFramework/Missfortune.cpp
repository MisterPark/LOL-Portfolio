#include "stdafx.h"
#include "Missfortune.h"

Missfortune::Missfortune()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"missfortune");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
}

Missfortune::~Missfortune()
{
}

void Missfortune::Initialize()
{
}

void Missfortune::Release()
{
}

void Missfortune::Update()
{
	Champion::Update();
}
