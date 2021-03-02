#include "stdafx.h"
#include "DamageCalc.h"

Engine::DamageCalc::DamageCalc()
{
}

Engine::DamageCalc::~DamageCalc()
{
}

float Engine::DamageCalc::Calc_Defense(float _damage, UnitStat* _myStat, UnitStat* _targetStat)
{
	float targetArmor = _targetStat->armor.GetValue();
	float myPenetrate = _myStat->adPenetrate.GetValue();
	float myPenetratePer = _myStat->adPenetratePercent.GetValue() * 0.01f;

	float finalDamage = (100 / (100 + targetArmor - (targetArmor * myPenetratePer + myPenetrate))) * _damage;
	return finalDamage;
}
