#include "stdafx.h"
#include "Ahri.h"

Ahri::Ahri()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"ahri");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);

	anim->SetLoop((int)UnitState::IDLE1, true);

	faceCircleTexkey = L"ahri_circle";
	faceSquareTexkey = L"ahri_square";
	// 스킬 아이콘
	qTexKey = L"ahri_q";
	wTexKey = L"ahri_w";
	eTexKey = L"ahri_e";
	rTexKey = L"ahri_r";
	passiveTexKey = L"ahri_passive";

	SetHP(526.f);
	SetHPRegen(5.5f);
	SetMP(418.f);
	SetMPRegen(8.f);
	SetAttackDamage(53.04f);
	SetAttackPerSec(0.668f);
	SetArmor(20.88f);
	SetMagicResistance(30.f);
	SetAttackRange(5.5f);
	SetMovementSpeed(3.3f);
}

Ahri::~Ahri()
{
}

void Ahri::Initialize()
{
}

void Ahri::Release()
{
}

void Ahri::Update()
{
	Champion::Update();
}
