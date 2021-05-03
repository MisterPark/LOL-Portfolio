#include "stdafx.h"
#include "Jinx.h"
#include "Skill_RangeAttack.h"
#include "ChampionSubTree.h"

Jinx::Jinx()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"jinx");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	faceCircleTexkey = L"jinx_circle";
	faceSquareTexkey = L"jinx_square";
	// 스킬 아이콘
	qTexKey = L"jinx_q1";
	wTexKey = L"jinx_w";
	eTexKey = L"jinx_e";
	rTexKey = L"jinx_r";
	passiveTexKey = L"jinx_passive";

	stat->SetBaseValue(StatType::MaxHealth, 610.f);
	stat->SetBaseValue(StatType::Health, 610.f);
	stat->SetBaseValue(StatType::HealthRegen, 3.75f);
	stat->SetBaseValue(StatType::MaxMana, 245.6f);
	stat->SetBaseValue(StatType::Mana, 245.6f);
	stat->SetBaseValue(StatType::ManaRegen, 6.5f);
	stat->SetBaseValue(StatType::AttackDamage, 57.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.625f);
	stat->SetBaseValue(StatType::Armor, 28.f);
	stat->SetBaseValue(StatType::MagicResistance, 30.f);
	stat->SetBaseValue(StatType::Range, 5.25f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.25f);

	skillList[(int)SkillIndex::Attack] = new Skill_RangeAttack(this);

	ChampionSubTree* subTree = new ChampionSubTree(this);
	bt->SetRoot(subTree);
}

Jinx::~Jinx()
{
}

void Jinx::Initialize()
{
}

void Jinx::Release()
{
}

void Jinx::Update()
{
	Champion::Update();
}
