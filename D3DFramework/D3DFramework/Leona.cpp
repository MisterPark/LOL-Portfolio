#include "stdafx.h"
#include "Leona.h"

Leona::Leona()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"leona");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
}

Leona::~Leona()
{
}

void Leona::Initialize()
{
}

void Leona::Release()
{
}

void Leona::Update()
{
	Champion::Update();
}
