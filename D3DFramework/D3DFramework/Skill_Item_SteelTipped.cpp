#include "stdafx.h"
#include "Skill_Item_SteelTipped.h"
#include "Unit.h"

Skill_Item_SteelTipped::Skill_Item_SteelTipped(Unit* _hostUnit)
{
	skillName = ItemSkillName::ManaCharge;
	host = _hostUnit;
	coolTimeTick = coolTime = 4.f;
}

Skill_Item_SteelTipped::~Skill_Item_SteelTipped()
{
	if (buffSkill != nullptr)
		buffSkill->duration = 0.f;
}

void Skill_Item_SteelTipped::Start()
{
}

void Skill_Item_SteelTipped::Passive()
{
	if (buffSkill == nullptr) {
		buffSkill = new Buff_Item_SteelTipped(host, 20.f, DamageKind::AD);
		host->stat->AddBuff(buffSkill);
	}
	return;
}

void Skill_Item_SteelTipped::Active()
{
	End();
}


void Skill_Item_SteelTipped::End()
{
	Skill::End();
}

Skill* Skill_Item_SteelTipped::Clone()
{
	return new Skill_Item_SteelTipped(nullptr);
}
