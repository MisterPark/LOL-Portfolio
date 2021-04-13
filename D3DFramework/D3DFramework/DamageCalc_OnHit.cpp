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
	float increaseDamageAD = 0.f;
	float increaseDamageAP = 0.f;
	for (auto& _buff : *_myStat->GetBuffList()) {
		Buff_OnHit* onHit = dynamic_cast<Buff_OnHit*>(_buff);
		if (onHit == nullptr)
			continue;
		if (onHit->damageKind == DamageKind::AD) {
			increaseDamageAD += onHit->basicDamage;
			increaseDamageAD += _myStat->GetValue(StatType::AttackDamage)  * onHit->weightDamage;
		}
		else if (onHit->damageKind == DamageKind::AP) {
			increaseDamageAP += onHit->basicDamage;
			increaseDamageAP += _myStat->GetValue(StatType::AttackDamage) * onHit->weightDamage;	
		}
	}

	if (damageKind == DamageKind::TrueDamage) {
		*_damage += increaseDamageAD + increaseDamageAP;
		return;
	}

	increaseDamageAD -= increaseDamageAD * (_targetStat->GetValue(StatType::DamageReduction));
	damageKind = DamageKind::AD;
	*_damage += Calc_Defense(increaseDamageAD, _myStat, _targetStat);

	increaseDamageAP -= increaseDamageAP * (_targetStat->GetValue(StatType::DamageReduction));
	damageKind = DamageKind::AP;
	*_damage += Calc_Defense(increaseDamageAP, _myStat, _targetStat);
}

DamageCalc_OnHit* DamageCalc_OnHit::CreateCalc(DamageKind _damageKind)
{
	DamageCalc_OnHit* damageCalc = new DamageCalc_OnHit;
	//damageCalc->value = _value;
	damageCalc->damageKind = _damageKind;
	return damageCalc;
}
