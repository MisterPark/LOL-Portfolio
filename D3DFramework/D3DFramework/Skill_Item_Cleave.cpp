#include "stdafx.h"
#include "Skill_Item_Cleave.h"
#include "Unit.h"
#include "DamageCalc_Basic.h"

Skill_Item_Cleave::Skill_Item_Cleave(Unit* _hostUnit)
{
	host = _hostUnit;
	Add_DamageCalc(DamageCalc_Basic::CreateCalc(DamageKind::AD));
}

Skill_Item_Cleave::~Skill_Item_Cleave()
{
}

void Skill_Item_Cleave::Start()
{
	return;
}

void Skill_Item_Cleave::Passive()
{
	return;
}

void Skill_Item_Cleave::Active()
{
	End();
}


void Skill_Item_Cleave::End()
{
	Skill::End();
}

Skill* Skill_Item_Cleave::Clone()
{
	return new Skill_Item_Cleave(nullptr);
}

void Skill_Item_Cleave::OnHit(Unit* target, Skill* mySkill)
{
	if (mySkill != host->skillList[(int)SkillIndex::Attack])
		return;
	float targetDist = 2.f;
	Vector3 targetPos = target->transform->GetPos();
	float hostDamage = host->stat->GetValue(StatType::AttackDamage);
	
	for (Unit* iter : host->unitList)
	{
		if (iter->IsDead()) continue;
		if (host->team == Team::NEUTRAL) continue;
		if (iter == target) continue;
		if (host->team != iter->team)
		{
			Vector3 to = iter->transform->position - targetPos;
			float dist = to.Length();
			if (dist < targetDist)
			{
				float finalDamage = (hostDamage * 0.6f) - ((dist / 3.f) * hostDamage * 0.48f);
				Calc_FinalDamage(&finalDamage, host->stat, iter->stat);
				iter->TakeDamage(finalDamage);
				iter->SetLastAttacker(host);
			}
		}
	}

	return;
}
