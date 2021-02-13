#include "stdafx.h"
#include "Missfortune.h"
#include "GameRenderer.h"
Missfortune::Missfortune()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"missfortune");
	AddComponent(L"DynamicMesh", dmesh);
	dmesh->renderGroupID = RenderGroupID::Deferred;
	GameRenderer::Register(dmesh);
	anim->AttachToDynamicMesh(dmesh);

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
	DynamicMesh* dmesh = (DynamicMesh*)GetComponent(L"DynamicMesh");
	GameRenderer::Unregister(dmesh);
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
