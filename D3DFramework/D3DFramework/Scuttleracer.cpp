#include "stdafx.h"
#include "Scuttleracer.h"

Scuttleracer::Scuttleracer()
{
	transform->scale = { 0.012f, 0.012f, 0.012f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"scuttleracer");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);

	anim->SetLoop(UnitState::IDLE1, true);
}

Scuttleracer::~Scuttleracer()
{
}
