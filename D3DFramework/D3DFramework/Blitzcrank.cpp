#include "stdafx.h"
#include "Blitzcrank.h"
#include "GameRenderer.h"
Blitzcrank::Blitzcrank()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"blitzcrank");
	AddComponent(L"DynamicMesh", dmesh);
	dmesh->renderGroupID = RenderGroupID::Deferred;
	GameRenderer::Register(dmesh);
	anim->AttachToDynamicMesh(dmesh);

	faceCircleTexkey = L"blitzcrank_circle";
	faceSquareTexkey = L"blitzcrank_square";
	// 스킬 아이콘
	qTexKey = L"blitzcrank_q";
	wTexKey = L"blitzcrank_w";
	eTexKey = L"blitzcrank_e";
	rTexKey = L"blitzcrank_r";
	passiveTexKey = L"blitzcrank_passive";

	SetHP(582.6f);
	SetHPRegen(8.5f);
	SetMP(267.2f);
	SetMPRegen(8.5f);
	SetAttackDamage(61.54f);
	SetAttackPerSec(0.625f);
	SetArmor(37.f);
	SetMagicResistance(32.1f);
	SetAttackRange(1.25f);
	SetMovementSpeed(3.25f);
}

Blitzcrank::~Blitzcrank()
{
	DynamicMesh* dmesh = (DynamicMesh*)GetComponent(L"DynamicMesh");
	GameRenderer::Unregister(dmesh);
}

void Blitzcrank::Initialize()
{
}

void Blitzcrank::Release()
{
}

void Blitzcrank::Update()
{
	Champion::Update();
}
