﻿#include "stdafx.h"
#include "Skill_Heal.h"
#include "Unit.h"
#include "Buff.h"
#include "Buff_HealMoveSpeed.h"
#include "SphereCollider.h"
#include "DamageObject.h"
#include "EffectObject.h"

Skill_Heal::Skill_Heal(Unit* _hostUnit)
{
	coolTimeTick = coolTime = 5.f;//8.f;
	duration = 0.f;
	host = _hostUnit;
	level = 1;
}

Skill_Heal::~Skill_Heal()
{
}

void Skill_Heal::Start()
{
	if (GetCooltime() > 0.f)
		return;

	Skill::Start();

	Buff_HealMoveSpeed* movementSpeedBuff = new Buff_HealMoveSpeed(host);
	host->stat->AddBuff(movementSpeedBuff);


	Heal();
	SoundManager::GetInstance()->PlayOverlapSound(L"SpellHeal1.ogg", SoundChannel::PLAYER_EFFECT, 0.8f);
}

void Skill_Heal::Passive()
{
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}

}

void Skill_Heal::Active()
{
	End();

}


void Skill_Heal::End()
{
	Skill::End();
}

void Skill_Heal::Heal()
{
	float healAmount = 75.f + (host->stat->GetBaseValue(StatType::Level) * 15.f);
	host->stat->IncreaseBaseValue(StatType::Health, healAmount);

	// 아군유닛 힐
	Unit* targetUnit = nullptr;
	//bool targetingHeal = false;

	//Ray ray = Camera::main->ScreenPointToRay(Input::GetMousePosition());
	//RaycastHit hit;
	//int groundMask = LayerMask::GetMask(Layer::Ground);

	//RaycastHit info;
	//int unitMask = LayerMask::GetMask(Layer::Unit, Layer::Building);

	//if (Physics::Raycast(ray, &info, INFINITY, unitMask))
	//{	
	//	targetUnit = (Unit*)info.collider->gameObject;
	//	if (targetUnit == host) {
	//	}
	//	else if (dynamic_cast<DamageObject*>(targetUnit) != nullptr) {

	//	}
	//	else if (dynamic_cast<EffectObject*>(targetUnit) != nullptr) {

	//	}
	//	else if (targetUnit->team == host->team && !targetUnit->IsDead())
	//	{
	//		targetUnit->stat->IncreaseBaseValue(StatType::Health, healAmount);
	//		return;
	//	}
	//}

	//
	targetUnit = GetLostHpTeam(host->GetTransform()->GetPos(), 5.f);
	if (targetUnit != nullptr)
	{
		targetUnit->stat->IncreaseBaseValue(StatType::Health, healAmount);
	}

}

Unit* Skill_Heal::GetLostHpTeam(Vector3 point, float radius)
{
	float targetDist = radius; // 고정
	Unit* target = nullptr;
	float targetHp = 100000.f;

	for (Unit* iter : host->unitList)
	{
		if (iter->IsDead()) continue;
		if (host->team == iter->team)
		{
			Vector3 to = iter->transform->position - point;
			float dist = to.Length();
			float iterHp = iter->stat->GetBaseValue(StatType::Health);;
			if (dist < targetDist && targetHp > iterHp)
			{
				target = iter;
				targetHp = iterHp;
			}
		}
	}

	return target;
}

