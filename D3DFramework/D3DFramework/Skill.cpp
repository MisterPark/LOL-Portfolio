#include "stdafx.h"
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
	coolTimeTick = 0.f;
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

void Skill::OnHit(Unit* target)
{
}

void Skill::OnDamaged(float damage)
{
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
	return (coolTime - coolTimeTick);
}

float Skill::GetCooltime_Init()
{
	return coolTime;
}

bool Skill::TargetingSuccess(Unit* target)
{
	if (host == nullptr) return false;

	if (target->team != host->team)
		return true;
	return false;
}

void Skill::SetTarget(Unit* _target)
{
	host = _target;
}

