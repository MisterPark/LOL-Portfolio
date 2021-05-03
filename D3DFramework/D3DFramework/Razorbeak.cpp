#include "stdafx.h"
#include "Razorbeak.h"
#include "Buff_GarenWReduction.h"

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

	anim->SetLoop((int)State::IDLE1, true);

//	stat->SetBaseValue(StatType::Armor, 500.f);
	// Test용
	//Buff_GarenWReduction* testBuff = new Buff_GarenWReduction(this, 999.f, 0.5f);
	//stat->AddBuff(testBuff);
	//
	
	stat->SetBaseValue(StatType::MinionKilled, 2.f);
	stat->SetBaseValue(StatType::Experience, 30.f);
	hitSound.push_back(L"RazobeakAttack1.ogg");
	hitSound.push_back(L"RazobeakAttack2.ogg");
	hitSound.push_back(L"RazobeakAttack3.ogg");
	hitSound.push_back(L"RazobeakAttack4.ogg");
	hitSound.push_back(L"RazobeakAttack5.ogg");
	hitSound.push_back(L"RazobeakAttack6.ogg");
}

Razorbeak::~Razorbeak()
{

}
