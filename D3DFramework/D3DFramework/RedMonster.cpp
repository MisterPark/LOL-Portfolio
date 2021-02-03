#include "stdafx.h"
#include "RedMonster.h"

RedMonster::RedMonster()
{
	transform->scale = { 0.02f, 0.02f, 0.02f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_red");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);

	anim->SetLoop((int)UnitState::IDLE1, true);
}

RedMonster::~RedMonster()
{
}
