#include "stdafx.h"
#include "Garen.h"
#include "Animation.h"

Garen::Garen()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"garen");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
	SetAttackSpeed(2.f);
}

Garen::~Garen()
{
}

void Garen::Initialize()
{
}

void Garen::Release()
{
}

void Garen::Update()
{
	Champion::Update();
}
