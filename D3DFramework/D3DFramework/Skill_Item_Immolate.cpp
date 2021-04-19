#include "stdafx.h"
#include "Skill_Item_Immolate.h"
#include "Unit.h"
#include "DamageCalc_Basic.h"

Skill_Item_Immolate::Skill_Item_Immolate(Unit* _hostUnit)
{
	skillName = ItemSkillName::Immolate;
	host = _hostUnit;
	coolTimeTick = coolTime = 0.5f;
	Add_DamageCalc(DamageCalc_Basic::CreateCalc(DamageKind::AP));
}

Skill_Item_Immolate::~Skill_Item_Immolate()
{
}

void Skill_Item_Immolate::Start()
{
	return;
}

void Skill_Item_Immolate::Passive()
{
	coolTimeTick += Time::DeltaTime();
	

	if (coolTimeTick > coolTime)
	{
		coolTimeTick = 0.f;
		SkillAttack();
	}
	return;
}

void Skill_Item_Immolate::Active()
{
	if (tick > duration) {
		End();
		return;
	}
	host->agent->Pause();
	host->SetState(State::ATTACK1);

	tick += Time::DeltaTime();
}


void Skill_Item_Immolate::End()
{
	host->agent->Resume();
	Skill::End();
}

Skill* Skill_Item_Immolate::Clone()
{
	return new Skill_Item_Immolate(nullptr);
}

void Skill_Item_Immolate::SkillAttack()
{
	float targetDist = 2.f;
	Vector3 targetPos = host->transform->GetPos();
	//TODO 최대체력을 추가체력으로
	float hostHp = host->stat->GetValue(StatType::MaxHealth);
	float damage = hostHp * 0.005f + 6.f;

	for (Unit* iter : host->unitList)
	{
		if (iter->IsDead()) continue;
		if (host->team == Team::NEUTRAL) continue;

		if (host->team != iter->team)
		{
			Vector3 to = iter->transform->position - targetPos;
			float dist = to.Length();
			if (dist < targetDist)
			{
				float finalDamage = damage;
				Calc_FinalDamage(&finalDamage, host->stat, iter->stat);
				iter->TakeDamage(finalDamage);
				iter->SetLastAttacker(host);
			}
		}
	}
}