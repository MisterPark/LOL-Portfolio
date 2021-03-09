#include "stdafx.h"
#include "DamageCalc_OnHit.h"
#include "Stat.h"
#include "Buff_OnHit.h"

DamageCalc_OnHit::DamageCalc_OnHit()
{
}

DamageCalc_OnHit::~DamageCalc_OnHit()
{
}

void DamageCalc_OnHit::Calc(float* _damage, Stat* _myStat, Stat* _targetStat)
{
	if (trueDamage)
		return;
	
	float increaseDamage = 0.f;
	for (auto& _buff : *_myStat->GetBuffList()) {
		Buff_OnHit* onHit = dynamic_cast<Buff_OnHit*>(_buff);
		if (onHit == nullptr)
			continue;
		increaseDamage += onHit->basicDamage;
		increaseDamage += _myStat->GetValue(StatType::AttackDamage) * onHit->weightDamage;
	}

	*_damage += Calc_Defense(increaseDamage, _myStat, _targetStat);
}

DamageCalc_OnHit* DamageCalc_OnHit::CreateCalc(bool _trueDamage)
{
	DamageCalc_OnHit* damageCalc = new DamageCalc_OnHit;
	//damageCalc->value = _value;
	damageCalc->trueDamage = _trueDamage;
	return damageCalc;
}
