#include "stdafx.h"
#include "Monster.h"
#include "Plane.h"
#include "Rectangle.h"
#include "MinionFloatingBar.h"
#include "MonsterAI.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "DamageCalc_Basic.h"
#include "MonsterSubTree.h"
#include "Skill_Attack.h"
#include "Scuttleracer.h"

Monster::Monster()
{
	bar = (MinionFloatingBar*)SceneManager::GetCurrentScene()->CreateObject<MinionFloatingBar>(Layer::UI);
	bar->SetTarget(this);
	if(dynamic_cast<Scuttleracer*>(this) == nullptr)
		AddComponent<MonsterAI>(L"MonsterAI");
	collider->SetRadius(0.2f);
	collider->center = { 0.f,0.25f,0.f };

	stat->SetBaseValue(StatType::MaxHealth, 300.f);
	stat->SetBaseValue(StatType::Health, 300.f);
	stat->SetBaseValue(StatType::HealthRegen, 1.5f);
	stat->SetBaseValue(StatType::AttackDamage, 4.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.525f);
	stat->SetBaseValue(StatType::Range, 1.25f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.35f);
	stat->SetBaseValue(StatType::Experience, 50.f);
	stat->SetBaseValue(StatType::MaxExperience, INFINITY);
	stat->SetBaseValue(StatType::MinionKilled, 4.f);

	damageCalcList.emplace_back(DamageCalc_Basic::CreateCalc(DamageKind::AD));

	// 스킬
	skillList[(int)SkillIndex::Attack] = new Skill_Attack(this);

	MonsterSubTree* subTree = new MonsterSubTree(this);
	bt->SetRoot(subTree);
}

Monster::~Monster()
{
	bar = nullptr;
}

void Monster::Initialize()
{
	Unit::Initialize();
}

void Monster::Release()
{
	Unit::Release();
}

void Monster::Update()
{
	Unit::Update();
	
}

void Monster::OnCollisionEnter(Collider* target)
{
	if (dynamic_cast<Unit*>(target->gameObject))
	{
		Unit* unit = (Unit*)target->gameObject;
		if (unit->GetState() == State::RUN)
		{
			unit->PushedOut(this);
		}

	}
}
