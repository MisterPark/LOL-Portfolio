#include "stdafx.h"
#include "DamageCalc_LostHpPercent.h"
#include "UnitStat.h"
#include "Stat.h"

DamageCalc_LostHpPercent::DamageCalc_LostHpPercent()
{
}

DamageCalc_LostHpPercent::~DamageCalc_LostHpPercent()
{
}

void DamageCalc_LostHpPercent::Calc(float* _damage, UnitStat* _myStat, UnitStat* _targetStat)
{
	float targetLostHp = _targetStat->maxHp.GetValue() - _targetStat->hp.GetValue();
	float lostHpDamage = targetLostHp * (value * 0.01f);
	if (trueDamage) {
		*_damage += lostHpDamage;
		return;
	}

	*_damage += Calc_Defense(lostHpDamage, _myStat, _targetStat);
}

DamageCalc_LostHpPercent* DamageCalc_LostHpPercent::CreateCalc(float _value, bool _trueDamage)
{
	DamageCalc_LostHpPercent* damageCalc = new DamageCalc_LostHpPercent;
	damageCalc->value = _value;
	damageCalc->trueDamage = _trueDamage;
	return damageCalc;
}
