#include "stdafx.h"
#include "Skill_Item_Thorns.h"
#include "Unit.h"
#include "DamageCalc_Basic.h"

Skill_Item_Thorns::Skill_Item_Thorns(Unit* _hostUnit)
{
	host = _hostUnit;
	Add_DamageCalc(DamageCalc_Basic::CreateCalc(DamageKind::AP));
}

Skill_Item_Thorns::~Skill_Item_Thorns()
{
}

void Skill_Item_Thorns::Start()
{
	return;
}

void Skill_Item_Thorns::Passive()
{
	return;
}

void Skill_Item_Thorns::Active()
{
	End();
}


void Skill_Item_Thorns::End()
{
	Skill::End();
}

Skill_Item* Skill_Item_Thorns::Clone()
{
	return new Skill_Item_Thorns(nullptr);
}

void Skill_Item_Thorns::OnDamaged(Unit* target, Skill* targetSkill, float damage)
{
	if (targetSkill == target->skillList[(int)SkillIndex::Attack]) {
		float finalDamage = host->stat->GetValue(StatType::Armor) * 0.1f + 3.f;
		Calc_FinalDamage(&finalDamage, host->stat, target->stat);
		target->TakeDamage(finalDamage);
	}
}
