#include "stdafx.h"
#include "Skill_Garen_P.h"
#include "Unit.h"
#include "Buff.h"
#include "Buff_GarenPHealthRegen.h"

Skill_Garen_P::Skill_Garen_P(Unit* _hostUnit)
{
	coolTime_Init = 8.f;
	duration = 0.f;
	hostUnit = _hostUnit;
}

Skill_Garen_P::~Skill_Garen_P()
{
}

void Skill_Garen_P::Start()
{
	Skill::Start();

	coolTime = coolTime_Init;

}

void Skill_Garen_P::Passive()
{
	if (coolTime > 0.f) {
		coolTime -= Time::DeltaTime();
	}

	if (passiveBuff == nullptr && coolTime <= 0.f) {
		passiveBuff = new Buff_GarenPHealthRegen(hostUnit);
		hostUnit->stat->AddBuff(passiveBuff);
	}
	else if(coolTime > 0.f && passiveBuff != nullptr){
		passiveBuff->duration = 0.f;
		passiveBuff = nullptr;
	}

	//TODO: 스위치이용해서 맞으면 쿨타임 늘리기
}

void Skill_Garen_P::Active()
{
	//if (!active)
		//return;

	//if (duration <= 0.f) {
	//	End();
	//	return;
	//}

	////사용효과
	//duration -= Time::DeltaTime();
}


void Skill_Garen_P::End()
{
	Skill::End();
}
