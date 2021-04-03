#include "stdafx.h"
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
	buffDreadnought->duration = 0.f;

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

void Skill_Item_Dreadnought::OnAttackEnd()
{
	buffDreadnought->overlapCount = 0;
}