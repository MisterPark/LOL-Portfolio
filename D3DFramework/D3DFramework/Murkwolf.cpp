#include "stdafx.h"
#include "Murkwolf.h"

Murkwolf::Murkwolf()
{
	transform->scale = { 0.016f, 0.016f, 0.016f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_murkwolf");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);

	anim->SetLoop(UnitState::IDLE1, true);
}

Murkwolf::~Murkwolf()
{
}
