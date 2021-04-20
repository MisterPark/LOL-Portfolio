#include "stdafx.h"
#include "Skill_Item_Crescent.h"
#include "Unit.h"
#include "DamageCalc_Basic.h"

Skill_Item_Crescent::Skill_Item_Crescent(Unit* _hostUnit)
{
	skillName = ItemSkillName::Crescent;
	host = _hostUnit;
	coolTime = 1.f;
	coolTimeTick = coolTime;
	duration = 0.3f;
	level = 1;
	Add_DamageCalc(DamageCalc_Basic::CreateCalc(DamageKind::AD));
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
	if (tick > duration) {
		End();
		return;
	}
	host->agent->Pause();
	host->SetState(State::ATTACK1);

	tick += Time::DeltaTime();
}


void Skill_Item_Crescent::End()
{
	host->agent->Resume();
	Skill::End();
}

Skill* Skill_Item_Crescent::Clone()
{
	return new Skill_Item_Crescent(nullptr);
}

void Skill_Item_Crescent::SkillAttack()
{
	float targetDist = 3.f;
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