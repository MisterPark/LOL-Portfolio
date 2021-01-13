#include "stdafx.h"
#include "Ahri.h"

Ahri::Ahri()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"ahri");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);

	anim->SetLoop(UnitState::IDLE1, true);
}

Ahri::~Ahri()
{
}

void Ahri::Initialize()
{
}

void Ahri::Release()
{
}

void Ahri::Update()
{
	Champion::Update();
}
