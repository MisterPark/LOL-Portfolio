#include "stdafx.h"
#include "MurkwolfMini.h"

MurkwolfMini::MurkwolfMini()
{
	transform->scale = { 0.013f, 0.013f, 0.013f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_murkwolfmini_left");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->SetLoop((int)State::IDLE1, true);

	stat->SetBaseValue(StatType::Experience, 40.f);
	hitSound.push_back(L"WolfAttack1.ogg");
	hitSound.push_back(L"WolfAttack2.ogg");
	hitSound.push_back(L"WolfAttack3.ogg");
}

MurkwolfMini::~MurkwolfMini()
{
}
