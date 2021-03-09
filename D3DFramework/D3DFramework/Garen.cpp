#include "stdafx.h"
#include "Garen.h"
#include "Animation.h"
#include "SkinnedMeshRenderer.h"
#include "FogOfWarRenderer.h"
#include "DamageObject.h"
#include "DamageCalc_Basic.h"
#include "DamageCalc_LostHpPercent.h"
#include "DamageCalc_CurrentHpPercent.h"
#include "DamageCalc_MaxHpPercent.h"
#include "DamageCalc_OnHit.h"
#include "Skill_Garen_Q.h"
#include "Buff_GarenQAttack.h"

Garen::Garen()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"garen");
	AddComponent(L"DynamicMesh", dmesh);
	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	Engine::FogOfWarRenderer* fogOfWarRenderer = new Engine::FogOfWarRenderer(this, 4.f);

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
	stat->SetBaseValue(StatType::MaxHealth, 620.f);
	stat->SetBaseValue(StatType::Health, 620.f);
	stat->SetBaseValue(StatType::HealthRegen, 8.f);
	stat->SetBaseValue(StatType::MaxMana, 100.f);
	stat->SetBaseValue(StatType::Mana, 100.f);
	stat->SetBaseValue(StatType::ManaRegen, 0.f);
	stat->SetBaseValue(StatType::AttackDamage, 66.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.625f);
	stat->SetBaseValue(StatType::Armor, 36.f);
	stat->SetBaseValue(StatType::MagicResistance, 32.1f);
	stat->SetBaseValue(StatType::Range, 1.75f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.4f);

	//stat->SetBaseValue(StatType::ArmorPenetrationPercent, 0.3f);
	damageCalcList.emplace_back(DamageCalc_Basic::CreateCalc());
	damageCalcList.emplace_back(DamageCalc_OnHit::CreateCalc());

	// 스킬
	skillList[(int)SkillIndex::Q] = new Skill_Garen_Q(this);
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

void Garen::Attacked()
{
	stat->RemoveBuff<Buff_GarenQAttack>();
}

//void Garen::Spell3()
//{
//	DamageObject* damageObj = (DamageObject*)SceneManager::GetCurrentScene()->CreateObject<DamageObject>(Layer::Unit);
//	damageObj->Set_DamageObject(this, transform->GetPos(), 7.f, this->team, stat->GetValue(StatType::AttackDamage) * 0.f, 2.f, 0.5f);
//	damageObj->Set_ObjectFollow(this);
//	//제일처음에 Basic만 잘 입혀줄것
//	damageObj->Add_DamageCalc(DamageCalc_Basic::CreateCalc());
//	//damageObj->Add_DamageCalc(DamageCalc_LostHpPercent::CreateCalc(0.1f));
//	damageObj->Add_DamageCalc(DamageCalc_CurrentHpPercent::CreateCalc(0.1f));
//	//damageObj->Add_DamageCalc(DamageCalc_MaxHpPercent::CreateCalc(0.1f));
//}


void Garen::SkillQAction()
{
}

void Garen::SkillWAction()
{
}

void Garen::SkillEAction()
{
}

void Garen::SkillRAction()
{
}

