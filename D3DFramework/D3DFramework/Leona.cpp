#include "stdafx.h"
#include "Leona.h"
#include "Skill_Attack.h"
#include "ChampionSubTree.h"

Leona::Leona()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"leona");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	faceCircleTexkey = L"leona_circle";
	faceSquareTexkey = L"leona_square";
	// 스킬 아이콘
	qTexKey = L"leona_q";
	wTexKey = L"leona_w";
	eTexKey = L"leona_e";
	rTexKey = L"leona_r";
	passiveTexKey = L"leona_passive";

	stat->SetBaseValue(StatType::MaxHealth, 576.16f);
	stat->SetBaseValue(StatType::Health, 576.16f);
	stat->SetBaseValue(StatType::HealthRegen, 8.5f);
	stat->SetBaseValue(StatType::MaxMana, 302.2f);
	stat->SetBaseValue(StatType::Mana, 302.2f);
	stat->SetBaseValue(StatType::ManaRegen, 6.f);
	stat->SetBaseValue(StatType::AttackDamage, 60.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.625f);
	stat->SetBaseValue(StatType::Armor, 47.f);
	stat->SetBaseValue(StatType::MagicResistance, 32.1f);
	stat->SetBaseValue(StatType::Range, 1.25f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.35f);

	skillList[(int)SkillIndex::Attack] = new Skill_Attack(this);

	ChampionSubTree* subTree = new ChampionSubTree(this);
	bt->SetRoot(subTree);
}

Leona::~Leona()
{
}

void Leona::Initialize()
{
}

void Leona::Release()
{
}

void Leona::Update()
{
	Champion::Update();
}
