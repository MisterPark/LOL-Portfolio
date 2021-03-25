#include "stdafx.h"
#include "Skill_Garen_P.h"
#include "Unit.h"
#include "Buff.h"
#include "Buff_GarenPHealthRegen.h"

Skill_Garen_P::Skill_Garen_P(Unit* _hostUnit)
{
	coolTime = 8.f;
	duration = 0.f;
	host = _hostUnit;
}

Skill_Garen_P::~Skill_Garen_P()
{
}

void Skill_Garen_P::Start()
{
	if (GetCooltime() > 0.f)
		return;

	Skill::Start();

	coolTimeTick = coolTime;

}

void Skill_Garen_P::Passive()
{
	if (coolTimeTick > 0.f) {
		coolTimeTick -= Time::DeltaTime();
	}

	if (passiveBuff == nullptr && coolTimeTick <= 0.f) {
		passiveBuff = new Buff_GarenPHealthRegen(host);
		host->stat->AddBuff(passiveBuff);
	}
	else if(coolTimeTick > 0.f && passiveBuff != nullptr){
		passiveBuff->duration = 0.f;
		passiveBuff = nullptr;
	}

	if (host->hitList.size() == 0)
	{
		coolTimeTick = 0.f;
	}
	else {
		Unit::HitInfo lastHitInfo = host->hitList.back();
		if (lastHitInfo.tick > 8.f)
			coolTimeTick = 0.f;
		else
			coolTimeTick = coolTime - lastHitInfo.tick;
	}

}

void Skill_Garen_P::Active()
{
	End();
}


void Skill_Garen_P::End()
{
	Skill::End();
}
