#include "stdafx.h"
#include "Skill_Item_Dreadnought.h"
#include "Buff_Item_Dreadnought.h"
#include "Unit.h"
#include "Stat.h"

Skill_Item_Dreadnought::Skill_Item_Dreadnought(Unit* _hostUnit)
{
	duration = 0.f;
	host = _hostUnit;
}

Skill_Item_Dreadnought::~Skill_Item_Dreadnought()
{
	//if (buffDreadnought != nullptr) {
	//	if (buffDreadnought->overlapCount == 1)
	//		buffDreadnought->duration = 0.f;
	//	else
	//		buffDreadnought->overlapCount--;
	//}
	if (host == nullptr)
		return;
	for (auto& buff : *host->stat->GetBuffList()) {
		if (buff->buffName == Buff::BuffName::Dreadnought) {
			if (buff->overlapCount == 1)
				buff->duration = 0.f;
			else
				buff->overlapCount--;
			break;
		}
	}
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


	//passiveTick += Time::DeltaTime() * 6.f;
	//if (passiveTick > 1.f) {
	//	passiveTick -= 1.f;
	//	if (passiveStack < 100)
	//		passiveStack++;
	//}

	//buffDreadnought->basicDamage = passiveStack;
	//buffDreadnought->modifiers.front().value = passiveStack * 0.006f;
}

void Skill_Item_Dreadnought::Active()
{
	return;
}

void Skill_Item_Dreadnought::End()
{
	return;
}

Skill* Skill_Item_Dreadnought::Clone()
{
	return new Skill_Item_Dreadnought(nullptr);
}

void Skill_Item_Dreadnought::OnAttackEnd()
{
	if (buffDreadnought != nullptr) {
		buffDreadnought->overlapCount = 0;
	}
}