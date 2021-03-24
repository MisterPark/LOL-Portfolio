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

void Skill::Use()
{
	Start();
}

void Skill::Start()
{
	active = true;
	tick = duration;
	coolTimeTick = coolTime;
}

void Skill::Passive()
{
}

void Skill::Active()
{
}

void Skill::End()
{
	active = false;
	tick = 0.f;
}

bool Skill::InRange()
{
	return true;
}

bool Skill::IsActive()
{
	return active;
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

float Skill::GetCooltime()
{
	return coolTimeTick;
}

float Skill::GetCooltime_Init()
{
	return coolTime;
}

