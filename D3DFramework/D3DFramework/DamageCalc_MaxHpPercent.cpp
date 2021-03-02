#include "stdafx.h"
#include "DamageCalc_MaxHpPercent.h"
#include "UnitStat.h"
#include "Stat.h"

DamageCalc_MaxHpPercent::DamageCalc_MaxHpPercent()
{
}

DamageCalc_MaxHpPercent::~DamageCalc_MaxHpPercent()
{
}

void DamageCalc_MaxHpPercent::Calc(float* _damage, UnitStat* _myStat, UnitStat* _targetStat)
{
	float maxHpDamage = _targetStat->maxHp.GetValue() * (value * 0.01f);
	if (trueDamage) {
		*_damage += maxHpDamage;
		return;
	}

	*_damage += Calc_Defense(maxHpDamage, _myStat, _targetStat);
}

DamageCalc_MaxHpPercent* DamageCalc_MaxHpPercent::CreateCalc(float _value, bool _trueDamage)
{
	DamageCalc_MaxHpPercent* damageCalc = new DamageCalc_MaxHpPercent;
	damageCalc->value = _value;
	damageCalc->trueDamage = _trueDamage;
	return damageCalc;
}
