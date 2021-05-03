#include "stdafx.h"
#include "Krug.h"

Krug::Krug()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_krug");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->SetLoop((int)State::IDLE1, true);
	stat->SetBaseValue(StatType::Experience, 40.f);
	hitSound.push_back(L"KrugAttack3.ogg");
}

Krug::~Krug()
{
}
