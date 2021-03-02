#include "stdafx.h"
#include "Razorbeak.h"

Razorbeak::Razorbeak()
{
	transform->scale = { 0.016f, 0.016f, 0.016f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_razorbeak");
	AddComponent(L"DynamicMesh", dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->AttachToDynamicMesh(dmesh);

	anim->SetLoop((int)UnitState::IDLE1, true);
	SetArmor(300.f);
}

Razorbeak::~Razorbeak()
{

}
