#include "stdafx.h"
#include "Skill_Item_Nimble.h"
#include "Unit.h"
#include "Buff_Item_Nimble.h"

Skill_Item_Nimble::Skill_Item_Nimble(Unit* _hostUnit)
{
	host = _hostUnit;
}

Skill_Item_Nimble::~Skill_Item_Nimble()
{
}

void Skill_Item_Nimble::Start()
{
	return;
}

void Skill_Item_Nimble::Passive()
{
	return;
}

void Skill_Item_Nimble::Active()
{
	End();
}


void Skill_Item_Nimble::End()
{
	Skill::End();
}

void Skill_Item_Nimble::OnHit(Unit* target, Skill* mySkill)
{
	float speed = 0.f;
	if (host->stat->GetValue(StatType::Range) < 3.f)
		speed = 0.2f;
	else
		speed = 0.1f;

	Buff_ItemNimble* buff = new Buff_ItemNimble(host, 2.f, speed);
	host->stat->AddBuff(buff);

	return;
}
