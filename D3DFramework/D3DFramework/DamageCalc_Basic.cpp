#include "stdafx.h"
#include "DamageCalc_Basic.h"
#include "UnitStat.h"
#include "Stat.h"

DamageCalc_Basic::DamageCalc_Basic()
{
}

DamageCalc_Basic::~DamageCalc_Basic()
{
}

void DamageCalc_Basic::Calc(float* _damage, UnitStat* _myStat, UnitStat* _targetStat)
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
