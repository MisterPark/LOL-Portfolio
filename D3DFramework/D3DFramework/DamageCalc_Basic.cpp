#include "stdafx.h"
#include "DamageCalc_Basic.h"
#include "Stat.h"

DamageCalc_Basic::DamageCalc_Basic()
{
}

DamageCalc_Basic::~DamageCalc_Basic()
{
}

void DamageCalc_Basic::Calc(float* _damage, Stat* _myStat, Stat* _targetStat)
{
	if (damageKind == DamageKind::TrueDamage)
		return;

	*_damage -= *_damage * (_targetStat->GetValue(StatType::DamageReduction));
	*_damage = Calc_Defense(*_damage, _myStat, _targetStat);
}

DamageCalc_Basic* DamageCalc_Basic::CreateCalc(DamageKind _damageKind)
{
	DamageCalc_Basic* damageCalc = new DamageCalc_Basic;
	//damageCalc->value = _value;
	damageCalc->damageKind = _damageKind;
	return damageCalc;
}
