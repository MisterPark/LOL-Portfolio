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
	firstHit = false;
	hitList.clear();
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

void Skill::OnHit(Unit* target, Skill* mySkill)
{
}

void Skill::OnDamaged(Unit* target, Skill* targetSkill, float damage)
{
}

void Skill::OnKilled(Unit* target)
{
}

void Skill::OnThisSkillHit(Unit* target)
{
	if (!firstHit) {
		OnOtherSkillStart(this);
		firstHit = true;
	}
}

void Skill::OnOtherSkillStart(Skill* otherSkill)
{
}

void Skill::OnTargetFirstHit(Unit* target, Skill* mySkill)
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

void Skill::Calc_TakeDamege(float _baseDamage)
{
	Unit* target = host->attackTarget;
	target->SetLastAttacker(host);
	float finalDamage = _baseDamage;
	Calc_FinalDamage(&finalDamage, host->stat, target->stat);
	target->TakeDamage(finalDamage);
	
	for (auto& unit : hitList)
	{
		if (unit == target)
			return;
	}
	hitList.push_back(target);
	host->OnTargetFirstHit(target, this);
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
	if (target->team != host->team)
		return true;
	return false;
}

