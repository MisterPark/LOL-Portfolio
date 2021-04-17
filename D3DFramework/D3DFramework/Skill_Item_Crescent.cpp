#include "stdafx.h"
#include "Skill_Item_Crescent.h"
#include "Unit.h"

Skill_Item_Crescent::Skill_Item_Crescent(Unit* _hostUnit)
{
	host = _hostUnit;
	coolTime = 20.f;
	coolTimeTick = coolTime;
	duration = 0.f;
}

Skill_Item_Crescent::~Skill_Item_Crescent()
{
}

void Skill_Item_Crescent::Start()
{
	if (GetCooltime() > 0.f)
		return;

	Skill::Start();
	SkillAttack();
}

void Skill_Item_Crescent::Passive()
{
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}

	return;
}

void Skill_Item_Crescent::Active()
{
	End();
}


void Skill_Item_Crescent::End()
{
	Skill::End();
}

void Skill_Item_Crescent::SkillAttack()
{
	float targetDist = 2.f;
	Vector3 targetPos = host->transform->GetPos();
	float hostDamage = host->stat->GetValue(StatType::AttackDamage);

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
				float finalDamage = hostDamage * 0.75f;
				Calc_FinalDamage(&finalDamage, host->stat, iter->stat);
				iter->TakeDamage(finalDamage);
				iter->SetLastAttacker(host);
			}
		}
	}
}