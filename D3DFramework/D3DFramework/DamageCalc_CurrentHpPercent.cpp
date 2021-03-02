#include "stdafx.h"
#include "DamageCalc_CurrentHpPercent.h"
#include "UnitStat.h"
#include "Stat.h"

DamageCalc_CurrentHpPercent::DamageCalc_CurrentHpPercent()
{
}

DamageCalc_CurrentHpPercent::~DamageCalc_CurrentHpPercent()
{
}

void DamageCalc_CurrentHpPercent::Calc(float* _damage, UnitStat* _myStat, UnitStat* _targetStat)
{
	float currentHpDamage = _targetStat->hp.GetValue() * (value * 0.01f);
	if (trueDamage) {
		*_damage += currentHpDamage;
		return;
	}

	*_damage += Calc_Defense(currentHpDamage, _myStat, _targetStat);
}

DamageCalc_CurrentHpPercent* DamageCalc_CurrentHpPercent::CreateCalc(float _value, bool _trueDamage)
{
	DamageCalc_CurrentHpPercent* damageCalc = new DamageCalc_CurrentHpPercent;
	damageCalc->value = _value;
	damageCalc->trueDamage = _trueDamage;
	return damageCalc;
}
