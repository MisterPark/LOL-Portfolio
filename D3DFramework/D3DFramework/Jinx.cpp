#include "stdafx.h"
#include "Jinx.h"

Jinx::Jinx()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"jinx");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
}

Jinx::~Jinx()
{
}

void Jinx::Initialize()
{
}

void Jinx::Release()
{
}

void Jinx::Update()
{
	Champion::Update();
}
