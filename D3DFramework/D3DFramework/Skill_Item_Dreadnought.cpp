﻿#include "stdafx.h"
#include "Skill_Item_Dreadnought.h"
#include "Buff_ItemDreadnought.h"
#include "Unit.h"
#include "Stat.h"

Skill_Item_Dreadnought::Skill_Item_Dreadnought(Unit* _hostUnit)
{
	duration = 0.f;
	host = _hostUnit;
}

Skill_Item_Dreadnought::~Skill_Item_Dreadnought()
{
	if (buffDreadnought != nullptr) {
		buffDreadnought->duration = 0.f;
	}

	//for (auto& buff : *host->stat->GetBuffList()) {
	//	if (buff->buffName == Buff::BuffName::Dreadnought) {
	//		buff->tick = buff->duration;
	//		break;
	//	}
	//}
}

void Skill_Item_Dreadnought::Start()
{
	return;
}

void Skill_Item_Dreadnought::Passive()
{
	if (host == nullptr) return;

	if (buffDreadnought == nullptr) {
		buffDreadnought = new Buff_ItemDreadnought(host, this, INFINITY, 0.f, 0.f, DamageKind::AP);
		host->stat->AddBuff(buffDreadnought);
	}


}

void Skill_Item_Dreadnought::Active()
{
	return;
}

void Skill_Item_Dreadnought::End()
{
	return;
}

Skill_Item* Skill_Item_Dreadnought::Clone()
{
	return new Skill_Item_Dreadnought(nullptr);
}

void Skill_Item_Dreadnought::OnAttackEnd()
{
	if (buffDreadnought != nullptr) {
		buffDreadnought->overlapCount = 0;
	}
}