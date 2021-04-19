﻿#include "stdafx.h"
#include "Skill_Item_SpellBlade.h"
#include "Unit.h"
#include "Buff_Item_SpellBlade.h"

Skill_Item_SpellBlade::Skill_Item_SpellBlade(Unit* _hostUnit)
{
	skillName = ItemSkillName::SpellBlade;
	host = _hostUnit;
	coolTimeTick = coolTime = 1.5f;
	level = 1;
}

Skill_Item_SpellBlade::~Skill_Item_SpellBlade()
{
	if (buffSkill != nullptr)
		buffSkill->duration = 0.f;
}

void Skill_Item_SpellBlade::Start()
{
	return;
}

void Skill_Item_SpellBlade::Passive()
{
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}
	return;
}

void Skill_Item_SpellBlade::Active()
{
	End();
}


void Skill_Item_SpellBlade::End()
{
	Skill::End();
}

Skill* Skill_Item_SpellBlade::Clone()
{
	return new Skill_Item_SpellBlade(nullptr);
}

void Skill_Item_SpellBlade::OnHit(Unit* target, Skill* mySkill)
{
	if (buffSkill != nullptr) {
		buffSkill->duration = 0.f;
		coolTimeTick = 0.f;
		buffSkill = nullptr;
	}
}

void Skill_Item_SpellBlade::OnOtherSkillStart(Skill* otherSkill)
{
	if (buffSkill == nullptr) {
		if (coolTimeTick >= coolTime) {
			buffSkill = new Buff_ItemSpellBlade(host, 4.f, host->stat->GetBaseValue(StatType::AttackDamage), DamageKind::AD);
			host->stat->AddBuff(buffSkill);
		}
	}
	else {
		buffSkill->tick = 0.f;
	}

}
