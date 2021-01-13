#include "stdafx.h"
#include "Gromp.h"

Gromp::Gromp()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_gromp");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);

	anim->SetLoop(UnitState::IDLE1, true);
}

Gromp::~Gromp()
{
}
