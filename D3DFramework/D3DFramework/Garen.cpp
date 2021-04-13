#include "stdafx.h"
#include "Garen.h"
#include "Animation.h"
#include "SkinnedMeshRenderer.h"
#include "FogOfWarRenderer.h"
#include "DistortionRenderer.h"
#include "DamageObject.h"
#include "DamageCalc_Basic.h"
#include "DamageCalc_LostHpPercent.h"
#include "DamageCalc_CurrentHpPercent.h"
#include "DamageCalc_MaxHpPercent.h"
#include "DamageCalc_OnHit.h"
#include "DamageCalc_Critical.h"
#include "Skill_Garen_P.h"
#include "Skill_Garen_Q.h"
#include "Skill_Garen_W.h"
#include "Skill_Garen_E.h"
#include "Skill_Garen_R.h"
#include "Skill_Ghost.h"
#include "Skill_Heal.h"
#include "Buff_GarenQAttack.h"
#include "ChampionSubTree.h"
#include "Skill_Attack.h"

Garen::Garen()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"garen");
	AddComponent(L"DynamicMesh", dmesh);
	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	Engine::FogOfWarRenderer* fogOfWarRenderer = new Engine::FogOfWarRenderer(this, 12.f);
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
	stat->SetBaseValue(StatType::CriticlaDamage, 1.f);
	// Test
	stat->SetBaseValue(StatType::SkillPoint, 18.f);
	stat->SetBaseValue(StatType::CriticlaChance, 0.5f);
	stat->SetBaseValue(StatType::Gold, 3000.f);
	
	damageCalcList.emplace_back(DamageCalc_Basic::CreateCalc(DamageKind::AD));
	damageCalcList.emplace_back(DamageCalc_Critical::CreateCalc());
	damageCalcList.emplace_back(DamageCalc_OnHit::CreateCalc(DamageKind::AD));

	// 스킬
	skillList[(int)SkillIndex::Attack] = new Skill_Attack(this);
	skillList[(int)SkillIndex::Passive] = new Skill_Garen_P(this);
	skillList[(int)SkillIndex::Q] = new Skill_Garen_Q(this);
	skillList[(int)SkillIndex::W] = new Skill_Garen_W(this);
	skillList[(int)SkillIndex::E] = new Skill_Garen_E(this);
	skillList[(int)SkillIndex::R] = new Skill_Garen_R(this);
	skillList[(int)SkillIndex::D] = new Skill_Ghost(this);
	skillList[(int)SkillIndex::F] = new Skill_Heal(this);

	ChampionSubTree* subTree = new ChampionSubTree(this);
	bt->SetRoot(subTree);
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

void Garen::OnAttackBegin()
{
	Unit::OnAttackBegin();
	anim->SetSpeed((int)State::Q, (*stat)[StatType::AttackSpeed]);
}

void Garen::OnAttackEnd()
{
	Unit::OnAttackEnd();
}

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

