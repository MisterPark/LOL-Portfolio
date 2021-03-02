#include "stdafx.h"
#include "Garen.h"
#include "Animation.h"
#include "SkinnedMeshRenderer.h"
#include "FogOfWarRenderer.h"
#include "DamageObject.h"

Garen::Garen()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"garen");
	AddComponent(L"DynamicMesh", dmesh);
	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	Engine::FogOfWarRenderer* fogOfWarRenderer = new Engine::FogOfWarRenderer(this, 15.f);

	renderer->SetMesh(dmesh);
	renderer->EnableRimLight(Vector3{ 1.f, 0.f, 0.f });
	AddComponent(L"renderer", renderer);
	AddComponent(L"fogRenderer", fogOfWarRenderer);

	anim->AttachToDynamicMesh(dmesh);

	// 얼굴 아이콘
	faceCircleTexkey = L"garen_circle";
	faceSquareTexkey = L"garen_square";
	// 스킬 아이콘
	qTexKey = L"garen_q";
	wTexKey = L"garen_w";
	eTexKey = L"garen_e1";
	rTexKey = L"garen_r";
	passiveTexKey = L"garen_passive";

	// 스탯
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
	printf("가렌 Q\n");
}

void Garen::Spell2()
{
}

void Garen::Spell3()
{
	DamageObject* damageObj = (DamageObject*)ObjectManager::GetInstance()->CreateObject<DamageObject>(Layer::Unit);
	damageObj->Set_DamageObject(this, transform->GetPos(), 5.f, this->team, GetAttackDamage() * 0.1f, 2.f, 0.2f);
}

void Garen::Spell4()
{
}
