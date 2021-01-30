#include "stdafx.h"
#include "Darius.h"

using namespace PKH;

Darius::Darius()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"darius");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);

	anim->SetLoop(UnitState::IDLE1, true);

	faceCircleTexkey = L"darius_circle";
	faceSquareTexkey = L"darius_square";
	// 스킬 아이콘
	qTexKey = L"darius_q";
	wTexKey = L"darius_w";
	eTexKey = L"darius_e";
	rTexKey = L"darius_r";
	passiveTexKey = L"darius_passive";

	SetHP(582.f);
	SetHPRegen(10.f);
	SetMP(263.f);
	SetMPRegen(6.6f);
	SetAttackDamage(64.f);
	SetAttackPerSec(0.625f);
	SetArmor(39.f);
	SetMagicResistance(32.1f);
	SetAttackRange(1.75f);
	SetMovementSpeed(3.4f);
}

Darius::~Darius()
{
}

void Darius::Initialize()
{
}

void Darius::Release()
{
}

void Darius::Update()
{
	Champion::Update();
}
