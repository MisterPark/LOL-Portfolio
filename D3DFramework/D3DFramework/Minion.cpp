#include "stdafx.h"
#include "Minion.h"
#include "MinionFloatingBar.h"
#include "MinionAI.h"
#include "SphereCollider.h"
#include "MinionSubTree.h"
#include "Skill_Attack.h"

#include "MinionSpawner.h"
#include "Champion.h"
#include "DamageCalc_Basic.h"

list<Minion*> Minion::minionList;

Minion::Minion()
{
	minionList.push_back(this);

	SetSpawnTime(INFINITY);
	
	bar = (MinionFloatingBar*)SceneManager::GetCurrentScene()->CreateObject<MinionFloatingBar>(Layer::UI);
	bar->SetTarget(this);

	ai =(MinionAI*)AddComponent<MinionAI>(L"AI");

	damageCalcList.emplace_back(DamageCalc_Basic::CreateCalc(DamageKind::AD));
	// 스킬
	skillList[(int)SkillIndex::Attack] = new Skill_Attack(this);

	MinionSubTree* subTree = new MinionSubTree(this);
	bt->SetRoot(subTree);

	Hide();
	stat->SetBaseValue(StatType::Experience, 12.f);
}

Minion::~Minion()
{
	minionList.remove(this);

	bar = nullptr;
	ai = nullptr;
}

void Minion::OnDeathEnd()
{
	MinionSpawner::IncreaseCount();
	Destroy();
}

void Minion::OnCollisionEnter(Collider* target)
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

void Minion::Die()
{
	Unit::Die();
	TakeExp();
}

void Minion::TakeExp()
{
	float targetDist = 10.f;
	Vector3 myPos = transform->GetPos();

	list<Unit*> championList;
	for (Unit* iter : unitList)
	{
		if (iter->IsDead()) continue;
		if (iter->team == team || iter->team == Team::NEUTRAL) continue;
		if (dynamic_cast<Champion*>(iter) != nullptr)
		{
			Vector3 to = iter->transform->position - myPos;
			float dist = to.Length();
			if (dist < targetDist)
			{
				championList.emplace_back(iter);
			}
		}
	}

	float exp = stat->GetBaseValue(StatType::Experience) / championList.size();
	for (auto& champion : championList)
	{
		champion->stat->IncreaseBaseValue(StatType::Experience, exp);
	}
}