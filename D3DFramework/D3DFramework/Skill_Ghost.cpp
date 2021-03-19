#include "stdafx.h"
#include "Skill_Ghost.h"
#include "Unit.h"
#include "Buff.h"
#include "Buff_Ghost.h"

Skill_Ghost::Skill_Ghost(Unit* _hostUnit)
{
	coolTime_Init = 0.1f;//8.f;
	duration = 0.f;
	hostUnit = _hostUnit;
}

Skill_Ghost::~Skill_Ghost()
{
}

void Skill_Ghost::Start()
{
	if (coolTime > 0.f)
		return;

	Skill::Start();

	float buffTime = (float)(24 + (24 / 18 * hostUnit->stat->GetBaseValue(StatType::Level))) * 0.01f;
	Buff_Ghost* movementSpeedBuff = new Buff_Ghost(hostUnit, 10.f, buffTime);
	hostUnit->stat->AddBuff(movementSpeedBuff);

	coolTime = coolTime_Init;


}

void Skill_Ghost::Passive()
{
	if (coolTime > 0.f) {
		coolTime -= Time::DeltaTime();
	}

}

void Skill_Ghost::Active()
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


void Skill_Ghost::End()
{
	Skill::End();
}
