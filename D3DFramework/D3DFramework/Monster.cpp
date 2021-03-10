#include "stdafx.h"
#include "Monster.h"
#include "Plane.h"
#include "Rectangle.h"
#include "MinionFloatingBar.h"
#include "MonsterAI.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "DamageCalc_Basic.h"

Monster::Monster()
{
	bar = (MinionFloatingBar*)SceneManager::GetCurrentScene()->CreateObject<MinionFloatingBar>(Layer::UI);
	bar->SetTarget(this);
	
	AddComponent<MonsterAI>(L"MonsterAI");
	collider->SetRadius(0.2f);
	collider->center = { 0.f,0.25f,0.f };

	stat->SetBaseValue(StatType::MaxHealth, 500.f);
	stat->SetBaseValue(StatType::Health, 500.f);
	stat->SetBaseValue(StatType::HealthRegen, 8.5f);
	stat->SetBaseValue(StatType::AttackDamage, 10.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.625f);
	stat->SetBaseValue(StatType::Range, 1.25f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.35f);

	damageCalcList.emplace_back(DamageCalc_Basic::CreateCalc());
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
