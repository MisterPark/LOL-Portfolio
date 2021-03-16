﻿#include "stdafx.h"
#include "Skill.h"
#include "Unit.h"
#include "DamageCalc.h"

Skill::Skill()
{
}

Skill::~Skill()
{
	for (auto calc : damageCalcList)
	{
		delete calc;
	}
}

bool Skill::IsAvailable()
{
	if (!active)
		return true;
	return false;
}

void Skill::Add_DamageCalc(DamageCalc* _damageCalc)
{
	damageCalcList.emplace_back(_damageCalc);
}

void Skill::Calc_FinalDamage(float* _damage, Stat* _myStat, Stat* _targetStat)
{
	for (auto& calc : damageCalcList)
	{
		calc->Calc(_damage, _myStat, _targetStat);
	}
}

