#include "stdafx.h"
#include "Diana.h"
#include "Skill_Attack.h"
#include "ChampionSubTree.h"

Diana::Diana()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"diana");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	faceCircleTexkey = L"diana_circle";
	faceSquareTexkey = L"diana_square";
	// 스킬 아이콘
	qTexKey = L"diana_q";
	wTexKey = L"diana_w";
	eTexKey = L"diana_e";
	rTexKey = L"diana_r";
	passiveTexKey = L"diana_passive";

	stat->SetBaseValue(StatType::MaxHealth, 570.f);
	stat->SetBaseValue(StatType::Health, 570.f);
	stat->SetBaseValue(StatType::HealthRegen, 7.5f);
	stat->SetBaseValue(StatType::MaxMana, 375.f);
	stat->SetBaseValue(StatType::Mana, 375.f);
	stat->SetBaseValue(StatType::ManaRegen, 8.f);
	stat->SetBaseValue(StatType::AttackDamage, 57.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.625f);
	stat->SetBaseValue(StatType::Armor, 31.f);
	stat->SetBaseValue(StatType::MagicResistance, 32.1f);
	stat->SetBaseValue(StatType::Range, 1.5f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.45f);

	skillList[(int)SkillIndex::Attack] = new Skill_Attack(this);

	ChampionSubTree* subTree = new ChampionSubTree(this);
	bt->SetRoot(subTree);
}

Diana::~Diana()
{
}

void Diana::Initialize()
{
}

void Diana::Release()
{
}

void Diana::Update()
{
	Champion::Update();
}
