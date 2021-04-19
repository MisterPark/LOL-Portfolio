#include "stdafx.h"
#include "Skill_Item_WitchsFocus.h"
#include "Buff_Item_WitchsFocus.h"
#include "Unit.h"

Skill_Item_WitchsFocus::Skill_Item_WitchsFocus(Unit* _hostUnit)
{
	skillName = ItemSkillName::WitchFocus;
	host = _hostUnit;
}

Skill_Item_WitchsFocus::~Skill_Item_WitchsFocus()
{
	if (buffWitchsFocus != nullptr) {
		buffWitchsFocus->duration = 0.f;
	}
}

void Skill_Item_WitchsFocus::Start()
{
	return;
}

void Skill_Item_WitchsFocus::Passive()
{
	if (buffWitchsFocus == nullptr) {
		buffWitchsFocus = new Buff_ItemWitchsFocus(host);
		host->stat->AddBuff(buffWitchsFocus);
	}
	buffWitchsFocus->modifiers.front().value = passiveStack * 0.5f;

}

void Skill_Item_WitchsFocus::Active()
{
	End();
}


void Skill_Item_WitchsFocus::End()
{
	Skill::End();
}

Skill* Skill_Item_WitchsFocus::Clone()
{
	return new Skill_Item_WitchsFocus(nullptr);
}

void Skill_Item_WitchsFocus::OnKilled(Unit* target)
{
	passiveStack++;
}
