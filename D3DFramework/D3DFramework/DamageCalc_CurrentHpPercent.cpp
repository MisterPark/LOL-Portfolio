#include "stdafx.h"
#include "DamageCalc_CurrentHpPercent.h"
#include "Stat.h"

DamageCalc_CurrentHpPercent::DamageCalc_CurrentHpPercent()
{
}

DamageCalc_CurrentHpPercent::~DamageCalc_CurrentHpPercent()
{
}

void DamageCalc_CurrentHpPercent::Calc(float* _damage, Stat* _myStat, Stat* _targetStat)
{
	float currentHpDamage = _targetStat->GetValue(StatType::Health) * value;
	if (damageKind == DamageKind::TrueDamage) {
		*_damage += currentHpDamage;
		return;
	}

	currentHpDamage -= currentHpDamage * (_targetStat->GetValue(StatType::DamageReduction));
	*_damage += Calc_Defense(currentHpDamage, _myStat, _targetStat);
}

DamageCalc_CurrentHpPercent* DamageCalc_CurrentHpPercent::CreateCalc(float _value, DamageKind _damageKind)
{
	DamageCalc_CurrentHpPercent* damageCalc = new DamageCalc_CurrentHpPercent;
	damageCalc->value = _value;
	damageCalc->damageKind = _damageKind;
	return damageCalc;
}
