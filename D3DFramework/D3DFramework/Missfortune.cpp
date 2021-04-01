#include "stdafx.h"
#include "Missfortune.h"
#include "Skill_RangeAttack.h"
#include "ChampionSubTree.h"

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

	skillList[(int)SkillIndex::Attack] = new Skill_RangeAttack(this);
	skillList[(int)SkillIndex::Passive] = new Skill_RangeAttack(this);
	skillList[(int)SkillIndex::Q] = new Skill_RangeAttack(this);
	skillList[(int)SkillIndex::W] = new Skill_RangeAttack(this);
	skillList[(int)SkillIndex::E] = new Skill_RangeAttack(this);
	skillList[(int)SkillIndex::R] = new Skill_RangeAttack(this);
	skillList[(int)SkillIndex::D] = new Skill_RangeAttack(this);
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
