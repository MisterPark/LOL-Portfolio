#include "stdafx.h"
#include "Garen.h"
#include "Animation.h"
#include "GameRenderer.h"
#include "SkinnedMeshRenderer.h"
Garen::Garen()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"garen");
	AddComponent(L"DynamicMesh", dmesh);
	KST::SkinnedMeshRenderer* renderer = new KST::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->AttachToDynamicMesh(dmesh);

	// æÛ±º æ∆¿Ãƒ‹
	faceCircleTexkey = L"garen_circle";
	faceSquareTexkey = L"garen_square";
	// Ω∫≈≥ æ∆¿Ãƒ‹
	qTexKey = L"garen_q";
	wTexKey = L"garen_w";
	eTexKey = L"garen_e1";
	rTexKey = L"garen_r";
	passiveTexKey = L"garen_passive";

	// Ω∫≈»
	SetHP(620.f);
	SetMP(100.f);
	SetHPRegen(8.f);
	SetMPRegen(0.f);
	SetAttackDamage(66.f);
	SetAttackPerSec(0.625f);
	SetAttackRange(1.75f);
	SetMovementSpeed(3.4f);
	SetArmor(36.f);
	SetMagicResistance(32.1f);



}

Garen::~Garen()
{
	DynamicMesh* dmesh = (DynamicMesh*)GetComponent(L"DynamicMesh");
	GameRenderer::Unregister(dmesh);
}

void Garen::Initialize()
{
}

void Garen::Release()
{
}

void Garen::Update()
{
	Champion::Update();
}

void Garen::Spell1()
{
	printf("∞°∑ª Q\n");
}

void Garen::Spell2()
{
}

void Garen::Spell3()
{
}

void Garen::Spell4()
{
}
