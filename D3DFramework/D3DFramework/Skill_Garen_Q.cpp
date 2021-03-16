#include "stdafx.h"
#include "Skill_Garen_Q.h"
#include "Unit.h"
#include "Buff.h"
#include "Buff_GarenQHaste.h"
#include "Buff_GarenQAttack.h"

Skill_Garen_Q::Skill_Garen_Q(Unit* _hostUnit)
{
	coolTime_Init = 0.5f;//8.f;
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

	durationSpeedTime = 2.5f;// 0.35f + level * 0.65f;
	Buff_GarenQHaste* speedBuff = new Buff_GarenQHaste(hostUnit, durationSpeedTime);
	hostUnit->stat->AddBuff(speedBuff);
	Buff_GarenQAttack* attackBuff = new Buff_GarenQAttack(hostUnit, 4.5f, 30.f, 1.5f);
	hostUnit->stat->AddBuff(attackBuff);

	coolTime = coolTime_Init;
	active = true;
	hostUnit->attackTick = 0.f;
	hostUnit->attackFlag = false;
	
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
}


void Skill_Garen_Q::End()
{
	active = false;
}
