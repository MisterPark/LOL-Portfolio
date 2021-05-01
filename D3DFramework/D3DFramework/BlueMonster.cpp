#include "stdafx.h"
#include "BlueMonster.h"
BlueMonster::BlueMonster()
{
	transform->scale = { 0.016f, 0.016f, 0.016f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_blue");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->SetLoop((int)State::IDLE1, true);

	hitSound.push_back(L"KrugAttack1.ogg");
}

BlueMonster::~BlueMonster()
{
}
