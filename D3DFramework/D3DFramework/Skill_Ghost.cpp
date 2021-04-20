#include "stdafx.h"
#include "Skill_Ghost.h"
#include "Unit.h"
#include "Buff.h"
#include "Buff_Ghost.h"

Skill_Ghost::Skill_Ghost(Unit* _hostUnit)
{
	coolTime = 0.1f;//8.f;
	duration = 0.f;
	host = _hostUnit;
	level = 1;
}

Skill_Ghost::~Skill_Ghost()
{
}

void Skill_Ghost::Start()
{
	if (GetCooltime() > 0.f)
		return;

	Skill::Start();

	float buffTime = (float)(24 + (24 / 18 * host->stat->GetBaseValue(StatType::Level))) * 0.01f;
	Buff_Ghost* movementSpeedBuff = new Buff_Ghost(host, 10.f, buffTime);
	host->stat->AddBuff(movementSpeedBuff);


}

void Skill_Ghost::Passive()
{
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}

}

void Skill_Ghost::Active()
{
	End();

}


void Skill_Ghost::End()
{
	Skill::End();
}
