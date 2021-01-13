#include "stdafx.h"
#include "Darius.h"

using namespace PKH;

Darius::Darius()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"darius");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);

	anim->SetLoop(UnitState::IDLE1, true);
}

Darius::~Darius()
{
}

void Darius::Initialize()
{
}

void Darius::Release()
{
}

void Darius::Update()
{
	Champion::Update();
}
