#include "stdafx.h"
#include "Ahri.h"
#include "ChampionSubTree.h"
#include "Skill_RangeAttack.h"

Ahri::Ahri()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"ahri");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->SetLoop((int)State::IDLE1, true);

	faceCircleTexkey = L"ahri_circle";
	faceSquareTexkey = L"ahri_square";
	// 스킬 아이콘
	qTexKey = L"ahri_q";
	wTexKey = L"ahri_w";
	eTexKey = L"ahri_e";
	rTexKey = L"ahri_r";
	passiveTexKey = L"ahri_passive";

	stat->SetBaseValue(StatType::MaxHealth, 526.f);
	stat->SetBaseValue(StatType::Health, 526.f);
	stat->SetBaseValue(StatType::HealthRegen, 5.5f);
	stat->SetBaseValue(StatType::MaxMana, 418.f);
	stat->SetBaseValue(StatType::Mana, 418.f);
	stat->SetBaseValue(StatType::ManaRegen, 8.f);
	stat->SetBaseValue(StatType::AttackDamage, 53.04f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.668f);
	stat->SetBaseValue(StatType::Armor, 20.88f);
	stat->SetBaseValue(StatType::MagicResistance, 30.f);
	stat->SetBaseValue(StatType::Range, 5.5f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.3f);

	skillList[(int)SkillIndex::Attack] = new Skill_RangeAttack(this);

	ChampionSubTree* subTree = new ChampionSubTree(this);
	bt->SetRoot(subTree);
}

Ahri::~Ahri()
{
}

void Ahri::Initialize()
{
}

void Ahri::Release()
{
}

void Ahri::Update()
{
	Champion::Update();
}
