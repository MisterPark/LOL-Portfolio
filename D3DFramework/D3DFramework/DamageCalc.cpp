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
	float targetArmor = 0.f, myPenetrate = 0.f, myPenetratePer = 0.f;
	if (damageKind == DamageKind::AD) {
		targetArmor = (*_targetStat)[StatType::Armor];
		myPenetrate = (*_myStat)[StatType::ArmorPenetration];
		myPenetratePer = (*_myStat)[StatType::ArmorPenetrationPercent] * 0.01f;
	}
	else if (damageKind == DamageKind::AP) {
		targetArmor = (*_targetStat)[StatType::MagicResistance];
		myPenetrate = (*_myStat)[StatType::MagicPenetration];
		myPenetratePer = (*_myStat)[StatType::MagicPenetrationPercent] * 0.01f;
	}

	float finalDamage = (100 / (100 + targetArmor - (targetArmor * myPenetratePer + myPenetrate))) * _damage;
	return finalDamage;
}
