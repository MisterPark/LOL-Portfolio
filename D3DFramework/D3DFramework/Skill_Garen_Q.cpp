#include "stdafx.h"
#include "Skill_Garen_Q.h"
#include "Unit.h"
#include "Buff.h"

Skill_Garen_Q::Skill_Garen_Q(Unit* _hostUnit)
{
	coolTime_Init = 8.f;
	duration = 0.f;
	hostUnit = _hostUnit;
}

Skill_Garen_Q::~Skill_Garen_Q()
{
}

void Skill_Garen_Q::Start()
{
	if (coolTime > 0.f)
		return;

	durationSpeedTime = 1.5f;// 0.35f + level * 0.65f;
	Buff* speedBuff = new Buff(hostUnit, durationSpeedTime);
	speedBuff->AddModifier(StatType::MovementSpeed, 0.3f, true);
	hostUnit->stat->AddBuff(speedBuff);

	coolTime = coolTime_Init;
	active = true;
	
}

void Skill_Garen_Q::Passive()
{
	if (coolTime > 0.f) {
		coolTime -= Time::DeltaTime();
	}

}

void Skill_Garen_Q::Active()
{
	//if (!active)
		//return;

	if (duration <= 0.f) {
		End();
		return;
	}

	//사용효과
	duration -= Time::DeltaTime();
	hostUnit->SetAttackState(State::Q);
}


void Skill_Garen_Q::End()
{
	active = false;
}
