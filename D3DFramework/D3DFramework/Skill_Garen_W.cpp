﻿#include "stdafx.h"
#include "Skill_Garen_W.h"
#include "Unit.h"
#include "Buff.h"
#include "Buff_GarenWReduction.h"
#include "Buff_GarenWShield.h"
#include "Buff_GarenWPassive.h"

Skill_Garen_W::Skill_Garen_W(Unit* _hostUnit)
{
	maxLevel = 5;
	coolTime_Init = 2.f;
	duration = 0.f;
	hostUnit = _hostUnit;
}

Skill_Garen_W::~Skill_Garen_W()
{
}

void Skill_Garen_W::Start()
{
	if (level == 0 || coolTime > 0.f)
		return;

	Skill::Start();

	reductionTime = 1.25f + level * 0.75f;
	Buff_GarenWReduction* reductionBuff = new Buff_GarenWReduction(hostUnit, reductionTime, 0.5f);//reductionValue);
	hostUnit->stat->AddBuff(reductionBuff);

	//TODO : 가렌W 지금은 최대체력계수로 되어있지만 나중에 추가체력계수로 바꿔야함
	float shield = 70 + hostUnit->stat->GetValue(StatType::MaxHealth) * 0.2f;
	Buff_GarenWShield* attackBuff = new Buff_GarenWShield(hostUnit, 0.75f, shield);
	hostUnit->stat->AddBuff(attackBuff);

	coolTime = coolTime_Init;

}

void Skill_Garen_W::Passive()
{
	if (level == 0)
		return;
	if (coolTime > 0.f) {
		coolTime -= Time::DeltaTime();
	}

	if (passiveBuff == nullptr) {
		passiveBuff = new Buff_GarenWPassive(hostUnit);
		hostUnit->stat->AddBuff(passiveBuff);
	}
	passiveBuff->modifiers.front().value = passiveStack * 0.25f;
	passiveBuff->modifiers.back().value = passiveStack * 0.25f;

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
