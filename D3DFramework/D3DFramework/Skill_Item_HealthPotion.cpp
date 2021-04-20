#include "stdafx.h"
#include "Skill_Item_HealthPotion.h"
#include "Unit.h"
#include "Buff_Item_HealthPotion.h"

Skill_Item_HealthPotion::Skill_Item_HealthPotion(Unit* _hostUnit)
{
	skillName = ItemSkillName::HealthPotion;
	host = _hostUnit;
	coolTime = 1.f;
	coolTimeTick = coolTime;
	duration = 0.f;
	level = 1;
}

Skill_Item_HealthPotion::~Skill_Item_HealthPotion()
{
}

void Skill_Item_HealthPotion::Start()
{
	if (GetCooltime() > 0.f)
		return;

	Skill::Start();

	float healthValue = 150.f;
	Buff_Item_HealthPotion* speedBuff = new Buff_Item_HealthPotion(host, 15.f, healthValue);
	host->stat->AddBuff(speedBuff);

	for (int i = 0; i < INVENTORY_MAX; i++) {
		Item* item = host->inventory.GetItem(i);
		if (item->skillList.front()->GetSkillName() == skillName) {
			//item->
		}
	}
}

void Skill_Item_HealthPotion::Passive()
{
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}

	return;
}

void Skill_Item_HealthPotion::Active()
{
	End();
}


void Skill_Item_HealthPotion::End()
{
	Skill::End();
}

Skill* Skill_Item_HealthPotion::Clone()
{
	return new Skill_Item_HealthPotion(nullptr);
}