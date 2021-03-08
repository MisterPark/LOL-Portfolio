#include "stdafx.h"
#include "DamageCalc.h"

Engine::DamageCalc::DamageCalc()
{
}

Engine::DamageCalc::~DamageCalc()
{
}

float Engine::DamageCalc::Calc_Defense(float _damage, Stat* _myStat, Stat* _targetStat)
{
	float targetArmor = (*_targetStat)[StatType::Armor];
	float myPenetrate = (*_myStat)[StatType::ArmorPenetration];
	float myPenetratePer = (*_myStat)[StatType::ArmorPenetrationPercent] * 0.01f;

	float finalDamage = (100 / (100 + targetArmor - (targetArmor * myPenetratePer + myPenetrate))) * _damage;
	return finalDamage;
}
