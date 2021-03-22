#include "stdafx.h"
#include "DamageCalc_MaxHpPercent.h"
#include "Stat.h"

DamageCalc_MaxHpPercent::DamageCalc_MaxHpPercent()
{
}

DamageCalc_MaxHpPercent::~DamageCalc_MaxHpPercent()
{
}

void DamageCalc_MaxHpPercent::Calc(float* _damage, Stat* _myStat, Stat* _targetStat)
{
	float maxHpDamage = _targetStat->GetValue(StatType::MaxHealth) * value;
	if (damageKind == DamageKind::TrueDamage) {
		*_damage += maxHpDamage;
		return;
	}

	maxHpDamage -= maxHpDamage * (_targetStat->GetValue(StatType::DamageReduction));
	*_damage += Calc_Defense(maxHpDamage, _myStat, _targetStat);
}

DamageCalc_MaxHpPercent* DamageCalc_MaxHpPercent::CreateCalc(float _value, DamageKind _damageKind)
{
	DamageCalc_MaxHpPercent* damageCalc = new DamageCalc_MaxHpPercent;
	damageCalc->value = _value;
	damageCalc->damageKind = _damageKind;
	return damageCalc;
}
