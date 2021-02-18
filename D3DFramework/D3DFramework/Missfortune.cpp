#include "stdafx.h"
#include "Missfortune.h"
Missfortune::Missfortune()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"missfortune");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	KST::SkinnedMeshRenderer* renderer = new KST::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	faceCircleTexkey = L"missfortune_circle";
	faceSquareTexkey = L"missfortune_square";
	// 스킬 아이콘
	qTexKey = L"missfortune_q";
	wTexKey = L"missfortune_w";
	eTexKey = L"missfortune_e";
	rTexKey = L"missfortune_r";
	passiveTexKey = L"missfortune_passive";

	SetHP(570.f);
	SetHPRegen(3.75f);
	SetMP(325.84f);
	SetMPRegen(8.f);
	SetAttackDamage(52.f);
	SetAttackPerSec(0.656f);
	SetArmor(28.f);
	SetMagicResistance(30.f);
	SetAttackRange(5.5f);
	SetMovementSpeed(3.25f);
}

Missfortune::~Missfortune()
{
}

void Missfortune::Initialize()
{
}

void Missfortune::Release()
{
}

void Missfortune::Update()
{
	Champion::Update();
}
