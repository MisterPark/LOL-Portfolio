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

	//생명력 흡수
	if(lifeSteal)
		_myStat->IncreaseBaseValue(StatType::Health, *_damage * _myStat->GetValue(StatType::LifeSteal));
}

DamageCalc_Basic* DamageCalc_Basic::CreateCalc(DamageKind _damageKind, bool _lifeSteal)
{
	DamageCalc_Basic* damageCalc = new DamageCalc_Basic;
	//damageCalc->value = _value;
	damageCalc->damageKind = _damageKind;
	damageCalc->lifeSteal = _lifeSteal;
	return damageCalc;
}
