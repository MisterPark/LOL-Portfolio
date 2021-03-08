#include "stdafx.h"
#include "DamageCalc_LostHpPercent.h"
#include "Stat.h"
#include "Stat.h"

DamageCalc_LostHpPercent::DamageCalc_LostHpPercent()
{
}

DamageCalc_LostHpPercent::~DamageCalc_LostHpPercent()
{
}

void DamageCalc_LostHpPercent::Calc(float* _damage, Stat* _myStat, Stat* _targetStat)
{
	float targetLostHp = _targetStat->GetValue(StatType::MaxHealth) - _targetStat->GetValue(StatType::Health);
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
