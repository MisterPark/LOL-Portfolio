#include "stdafx.h"
#include "Skill_MissFortune_P.h"
#include "Unit.h"
#include "Buff.h"
#include "DamageCalc_Basic.h"

Skill_MissFortune_P::Skill_MissFortune_P(Unit* _hostUnit)
{
	coolTime = 8.f;
	duration = 0.f;
	host = _hostUnit;
	Add_DamageCalc(DamageCalc_Basic::CreateCalc(DamageKind::AD));
}

Skill_MissFortune_P::~Skill_MissFortune_P()
{
}

void Skill_MissFortune_P::Start()
{
	if (GetCooltime() > 0.f)
		return;

	Skill::Start();

}

void Skill_MissFortune_P::Passive()
{
	return;
}

void Skill_MissFortune_P::Active()
{
	End();
}


void Skill_MissFortune_P::End()
{
	Skill::End();
}

void Skill_MissFortune_P::OnHit(Unit* target)
{
	if (lastAttack != target) {
		lastAttack = target;
		if (lastAttack == nullptr) return;
		float finalDamage = host->stat->GetValue(StatType::AttackDamage) * 0.5f;
		Calc_FinalDamage(&finalDamage, host->stat, lastAttack->stat);
		target->TakeDamage(finalDamage);
	}
}
