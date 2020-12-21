#include "stdafx.h"
#include "Blitzcrank.h"

Blitzcrank::Blitzcrank()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"blitzcrank");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
}

Blitzcrank::~Blitzcrank()
{
}

void Blitzcrank::Initialize()
{
}

void Blitzcrank::Release()
{
}

void Blitzcrank::Update()
{
	Champion::Update();
}
