#include "stdafx.h"
#include "Skill_Garen_W.h"
#include "Unit.h"
#include "Buff.h"
#include "Buff_GarenWReduction.h"
#include "Buff_GarenWShield.h"

Skill_Garen_W::Skill_Garen_W(Unit* _hostUnit)
{
	coolTime_Init = 2.f;
	duration = 0.f;
	hostUnit = _hostUnit;
}

Skill_Garen_W::~Skill_Garen_W()
{
}

void Skill_Garen_W::Start()
{
	Skill::Start();

	reductionTime = 2.f;// 1.25f + level * 0.75f;
	Buff_GarenWReduction* reductionBuff = new Buff_GarenWReduction(hostUnit, reductionTime, 0.5f);//reductionValue);
	hostUnit->stat->AddBuff(reductionBuff);

	//TODO : 가렌W 지금은 최대체력계수로 되어있지만 나중에 추가체력계수로 바꿔야함
	float shield = 70 + hostUnit->stat->GetValue(StatType::MaxHealth) * 0.2f;
	Buff_GarenWShield* attackBuff = new Buff_GarenWShield(hostUnit, 999.f, shield);
	hostUnit->stat->AddBuff(attackBuff);

	coolTime = coolTime_Init;

}

void Skill_Garen_W::Passive()
{
	if (coolTime > 0.f) {
		coolTime -= Time::DeltaTime();
	}

}

void Skill_Garen_W::Active()
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


void Skill_Garen_W::End()
{
	Skill::End();
}
