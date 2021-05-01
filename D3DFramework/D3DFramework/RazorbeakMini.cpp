#include "stdafx.h"
#include "RazorbeakMini.h"

RazorbeakMini::RazorbeakMini()
{
	transform->scale = { 0.011f, 0.011f, 0.011f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_razorbeakmini");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->SetLoop((int)State::IDLE1, true);

	stat->SetBaseValue(StatType::MinionKilled, 0.4f);

	hitSound.push_back(L"RazobeakAttack1.ogg");
	hitSound.push_back(L"RazobeakAttack3.ogg");
	hitSound.push_back(L"RazobeakAttack6.ogg");
}

RazorbeakMini::~RazorbeakMini()
{
}
