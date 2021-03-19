#include "stdafx.h"
#include "DamageCalc_Critical.h"
#include "Stat.h"

DamageCalc_Critical::DamageCalc_Critical()
{
}

DamageCalc_Critical::~DamageCalc_Critical()
{
}

void DamageCalc_Critical::Calc(float* _damage, Stat* _myStat, Stat* _targetStat)
{
	float random = (float)Random::Value(100);
	float myCriticalChance = _myStat->GetValue(StatType::CriticlaChance);
	if (myCriticalChance * 100.f < random)
		return;

	*_damage += *_damage * _myStat->GetValue(StatType::CriticlaDamage);
}

DamageCalc_Critical* DamageCalc_Critical::CreateCalc()
{
	DamageCalc_Critical* damageCalc = new DamageCalc_Critical;
	return damageCalc;
}
