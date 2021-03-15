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
	if (coolTime > 0.f)
		return;

	coolTime = coolTime_Init;
	active = true;

}

void Skill_Garen_P::Passive()
{
	if (coolTime > 0.f) {
		coolTime -= Time::DeltaTime();
	}

	//TODO 999.f 말고 -1.f  를 넣어서 예외처리 하고싶음(지속시간 없는것들)
	if (passiveBuff == nullptr && coolTime <= 0.f) {
		passiveBuff = new Buff_GarenPHealthRegen(hostUnit, 999.f);
		hostUnit->stat->AddBuff(passiveBuff);
	}
	else if(coolTime > 0.f && passiveBuff != nullptr){
		passiveBuff->duration = 0.f;
		passiveBuff = nullptr;
	}
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
	active = false;
}
