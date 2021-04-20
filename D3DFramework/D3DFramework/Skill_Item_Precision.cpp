#include "stdafx.h"
#include "Skill_Item_Precision.h"
#include "Minion.h"
#include "Monster.h"

Skill_Item_Precision::Skill_Item_Precision(Unit* _hostUnit)
{
	skillName = ItemSkillName::Precision;
	host = _hostUnit;
	level = 1;
}

Skill_Item_Precision::~Skill_Item_Precision()
{
}

void Skill_Item_Precision::Start()
{
}

void Skill_Item_Precision::Passive()
{
	return;
}

void Skill_Item_Precision::Active()
{
	End();
}


void Skill_Item_Precision::End()
{
	Skill::End();
}

Skill* Skill_Item_Precision::Clone()
{
	return new Skill_Item_Precision(nullptr);
}

void Skill_Item_Precision::OnDamaged(Unit* target, Skill* targetSkill, float* damage)
{
	if (dynamic_cast<Minion*>(target) != nullptr)
		target->TakeDamage(20.f);
	else if (dynamic_cast<Monster*>(target) != nullptr)
		target->TakeDamage(20.f);
}
