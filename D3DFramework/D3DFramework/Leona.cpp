#include "stdafx.h"
#include "Leona.h"
#include "GameRenderer.h"

Leona::Leona()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"leona");
	AddComponent(L"DynamicMesh", dmesh);
	dmesh->renderGroupID = RenderGroupID::Deferred;
	GameRenderer::Register(dmesh);
	anim->AttachToDynamicMesh(dmesh);

	faceCircleTexkey = L"leona_circle";
	faceSquareTexkey = L"leona_square";
	// 스킬 아이콘
	qTexKey = L"leona_q";
	wTexKey = L"leona_w";
	eTexKey = L"leona_e";
	rTexKey = L"leona_r";
	passiveTexKey = L"leona_passive";

	SetHP(576.16f);
	SetHPRegen(8.5f);
	SetMP(302.2f);
	SetMPRegen(6.f);
	SetAttackDamage(60.f);
	SetAttackPerSec(0.625f);
	SetArmor(47.f);
	SetMagicResistance(32.1f);
	SetAttackRange(1.25f);
	SetMovementSpeed(3.35f);
}

Leona::~Leona()
{
	DynamicMesh* dmesh = (DynamicMesh*)GetComponent(L"DynamicMesh");
	GameRenderer::Unregister(dmesh);
}

void Leona::Initialize()
{
}

void Leona::Release()
{
}

void Leona::Update()
{
	Champion::Update();
}
