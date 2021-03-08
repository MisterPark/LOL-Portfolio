#include "stdafx.h"
#include "DamageCalc_Basic.h"
#include "Stat.h"
#include "Stat.h"

DamageCalc_Basic::DamageCalc_Basic()
{
}

DamageCalc_Basic::~DamageCalc_Basic()
{
}

void DamageCalc_Basic::Calc(float* _damage, Stat* _myStat, Stat* _targetStat)
{
	if (trueDamage)
		return;

	*_damage = Calc_Defense(*_damage, _myStat, _targetStat);
}

DamageCalc_Basic* DamageCalc_Basic::CreateCalc(float _value, bool _trueDamage)
{
	DamageCalc_Basic* damageCalc = new DamageCalc_Basic;
	damageCalc->value = _value;
	damageCalc->trueDamage = _trueDamage;
	return damageCalc;
}
