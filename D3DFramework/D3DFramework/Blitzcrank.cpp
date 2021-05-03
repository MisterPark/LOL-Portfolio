#include "stdafx.h"
#include "Blitzcrank.h"
#include "Skill_Attack.h"
#include "ChampionSubTree.h"

Blitzcrank::Blitzcrank()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"blitzcrank");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	faceCircleTexkey = L"blitzcrank_circle";
	faceSquareTexkey = L"blitzcrank_square";
	// 스킬 아이콘
	qTexKey = L"blitzcrank_q";
	wTexKey = L"blitzcrank_w";
	eTexKey = L"blitzcrank_e";
	rTexKey = L"blitzcrank_r";
	passiveTexKey = L"blitzcrank_passive";

	stat->SetBaseValue(StatType::MaxHealth, 582.6f);
	stat->SetBaseValue(StatType::Health, 582.6f);
	stat->SetBaseValue(StatType::HealthRegen, 8.5f);
	stat->SetBaseValue(StatType::MaxMana, 267.2f);
	stat->SetBaseValue(StatType::Mana, 267.2f);
	stat->SetBaseValue(StatType::ManaRegen, 8.5f);
	stat->SetBaseValue(StatType::AttackDamage, 61.54f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.625f);
	stat->SetBaseValue(StatType::Armor, 37.f);
	stat->SetBaseValue(StatType::MagicResistance, 32.1f);
	stat->SetBaseValue(StatType::Range, 1.25f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.25f);

	skillList[(int)SkillIndex::Attack] = new Skill_Attack(this);

	ChampionSubTree* subTree = new ChampionSubTree(this);
	bt->SetRoot(subTree);
}

Blitzcrank::~Blitzcrank()
{
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
