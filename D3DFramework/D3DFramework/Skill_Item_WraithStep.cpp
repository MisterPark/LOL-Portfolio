#include "stdafx.h"
#include "Skill_Item_WraithStep.h"
#include "Unit.h"
#include "DamageCalc_Basic.h"
#include "Buff_Item_WraithStep.h"
#include "Buff_Item_WraithStep_P.h"

Skill_Item_WraithStep::Skill_Item_WraithStep(Unit* _hostUnit)
{
	host = _hostUnit;
	coolTime = 45.f;
	coolTimeTick = coolTime;
	duration = 0.f;
}

Skill_Item_WraithStep::~Skill_Item_WraithStep()
{
}

void Skill_Item_WraithStep::Start()
{
	if (GetCooltime() > 0.f)
		return;

	Skill::Start();

	float speedValue = 0.2f;
	Buff_Item_WraithStep* speedBuff = new Buff_Item_WraithStep(host, 6.f, speedValue);
	host->stat->AddBuff(speedBuff);
}

void Skill_Item_WraithStep::Passive()
{
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}
	passiveTick += Time::DeltaTime();

	if (passiveBuff == nullptr) {
		passiveBuff = new Buff_Item_WraithStep_P(host);
		host->stat->AddBuff(passiveBuff);
	}

	if (passiveTick > NON_COMBAT_TIME)
		passiveBuff->modifiers.front().value = 0.4f;
	else
		passiveBuff->modifiers.front().value = 0.f;
	return;
}

void Skill_Item_WraithStep::Active()
{
	End();
}


void Skill_Item_WraithStep::End()
{
	Skill::End();
}

void Skill_Item_WraithStep::OnHit(Unit* target, Skill* mySkill)
{
	passiveTick = 0.f;
}

void Skill_Item_WraithStep::OnDamaged(Unit* target, Skill* targetSkill, float damage)
{
	passiveTick = 0.f;
}
