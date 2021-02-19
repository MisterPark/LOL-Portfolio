#include "stdafx.h"
#include "Jinx.h"
Jinx::Jinx()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"jinx");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	KST::SkinnedMeshRenderer* renderer = new KST::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	faceCircleTexkey = L"jinx_circle";
	faceSquareTexkey = L"jinx_square";
	// 스킬 아이콘
	qTexKey = L"jinx_q1";
	wTexKey = L"jinx_w";
	eTexKey = L"jinx_e";
	rTexKey = L"jinx_r";
	passiveTexKey = L"jinx_passive";

	SetHP(610.f);
	SetHPRegen(3.75f);
	SetMP(245.6f);
	SetMPRegen(6.5f);
	SetAttackDamage(57.f);
	SetAttackPerSec(0.625f);
	SetArmor(28.f);
	SetMagicResistance(30.f);
	SetAttackRange(5.25f);
	SetMovementSpeed(3.25f);
}

Jinx::~Jinx()
{
}

void Jinx::Initialize()
{
}

void Jinx::Release()
{
}

void Jinx::Update()
{
	Champion::Update();
}
