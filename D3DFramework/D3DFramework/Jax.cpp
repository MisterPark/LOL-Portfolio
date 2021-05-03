#include "stdafx.h"
#include "Jax.h"
#include "SkinnedMeshRenderer.h"
#include "Skill_Attack.h"
#include "ChampionSubTree.h"

Jax::Jax()
{
	transform->scale = { 0.016f, 0.016f, 0.016f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"jax");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	faceCircleTexkey = L"jax_circle";
	faceSquareTexkey = L"jax_square";
	// 스킬 아이콘
	qTexKey = L"jax_q";
	wTexKey = L"jax_w";
	eTexKey = L"jax_e";
	rTexKey = L"jax_r";
	passiveTexKey = L"jax_passive";

	stat->SetBaseValue(StatType::MaxHealth, 592.8f);
	stat->SetBaseValue(StatType::Health, 592.8f);
	stat->SetBaseValue(StatType::HealthRegen, 8.5f);
	stat->SetBaseValue(StatType::MaxMana, 338.8f);
	stat->SetBaseValue(StatType::Mana, 338.8f);
	stat->SetBaseValue(StatType::ManaRegen, 7.5f);
	stat->SetBaseValue(StatType::AttackDamage, 68.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.638f);
	stat->SetBaseValue(StatType::Armor, 36.f);
	stat->SetBaseValue(StatType::MagicResistance, 31.25f);
	stat->SetBaseValue(StatType::Range, 1.25f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.5f);

	skillList[(int)SkillIndex::Attack] = new Skill_Attack(this);

	ChampionSubTree* subTree = new ChampionSubTree(this);
	bt->SetRoot(subTree);
}

Jax::~Jax()
{
}

void Jax::Initialize()
{
}

void Jax::Release()
{
}

void Jax::Update()
{
	Champion::Update();
}
