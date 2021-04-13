#include "stdafx.h"
#include "Missfortune.h"
#include "Skill_RangeAttack.h"
#include "ChampionSubTree.h"
#include "Skill_MissFortune_P.h"
#include "Skill_MissFortune_W.h"
#include "Skill_MissFortune_E.h"
#include "DamageCalc_Basic.h"
#include "DamageCalc_OnHit.h"
#include "DamageCalc_Critical.h"
#include "Skill_Ghost.h"

Missfortune::Missfortune()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"missfortune");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
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

	stat->SetBaseValue(StatType::MaxHealth, 570.f);
	stat->SetBaseValue(StatType::Health, 570.f);
	stat->SetBaseValue(StatType::HealthRegen, 3.75f);
	stat->SetBaseValue(StatType::MaxMana, 325.84f);
	stat->SetBaseValue(StatType::Mana, 325.84f);
	stat->SetBaseValue(StatType::ManaRegen, 8.f);
	stat->SetBaseValue(StatType::AttackDamage, 52.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.656f);
	stat->SetBaseValue(StatType::Armor, 28.f);
	stat->SetBaseValue(StatType::MagicResistance, 30.f);
	stat->SetBaseValue(StatType::Range, 5.5f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.25f);
	//Test
	stat->SetBaseValue(StatType::LifeSteal, 0.5f);

	damageCalcList.emplace_back(DamageCalc_Basic::CreateCalc(DamageKind::AD, true));
	damageCalcList.emplace_back(DamageCalc_Critical::CreateCalc());
	damageCalcList.emplace_back(DamageCalc_OnHit::CreateCalc(DamageKind::AD));

	skillList[(int)SkillIndex::Attack] = new Skill_RangeAttack(this);
	skillList[(int)SkillIndex::Passive] = new Skill_MissFortune_P(this);
	skillList[(int)SkillIndex::Q] = new Skill_RangeAttack(this);
	skillList[(int)SkillIndex::W] = new Skill_MissFortune_W(this);
	skillList[(int)SkillIndex::E] = new Skill_MissFortune_E(this);
	skillList[(int)SkillIndex::R] = new Skill_RangeAttack(this);
	skillList[(int)SkillIndex::D] = new Skill_Ghost(this);
	skillList[(int)SkillIndex::F] = new Skill_RangeAttack(this);

	ChampionSubTree* subTree = new ChampionSubTree(this);
	bt->SetRoot(subTree);
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
