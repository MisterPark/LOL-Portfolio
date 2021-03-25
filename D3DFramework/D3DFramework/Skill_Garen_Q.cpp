#include "stdafx.h"
#include "Skill_Garen_Q.h"
#include "Unit.h"
#include "Buff.h"
#include "Buff_GarenQHaste.h"
#include "Buff_GarenQAttack.h"

Skill_Garen_Q::Skill_Garen_Q(Unit* _hostUnit)
{
	maxLevel = 5;
	coolTime = 0.5f;//8.f;
	coolTimeTick = coolTime;
	duration = 0.f;
	host = _hostUnit;
}

Skill_Garen_Q::~Skill_Garen_Q()
{
}

void Skill_Garen_Q::Start()
{
	if (level == 0 || GetCooltime() > 0.f)
		return;

	Skill::Start();

	durationSpeedTime = 0.35f + level * 0.65f;
	Buff_GarenQHaste* speedBuff = new Buff_GarenQHaste(host, durationSpeedTime);
	host->stat->AddBuff(speedBuff);
	Buff_GarenQAttack* attackBuff = new Buff_GarenQAttack(host, 4.5f, 30.f * level, 1.5f, DamageKind::AD);
	host->stat->AddBuff(attackBuff);

	host->attackTick = 0.f;
	host->attackFlag = false;
	
}

void Skill_Garen_Q::Passive()
{
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}

}

void Skill_Garen_Q::Active()
{
	End();
}


void Skill_Garen_Q::End()
{
	Skill::End();
}
