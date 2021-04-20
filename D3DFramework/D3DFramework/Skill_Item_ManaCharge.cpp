#include "stdafx.h"
#include "Skill_Item_ManaCharge.h"
#include "Unit.h"
#include "Buff_Item_ManaCharge.h"
#include "Minion.h"
#define MaxChargeCount 3

Skill_Item_ManaCharge::Skill_Item_ManaCharge(Unit* _hostUnit)
{
	skillName = ItemSkillName::ManaCharge;
	host = _hostUnit;
	coolTimeTick = coolTime = 4.f;
	level = 1;
}

Skill_Item_ManaCharge::~Skill_Item_ManaCharge()
{
	if (buffSkill != nullptr)
		buffSkill->duration = 0.f;
}

void Skill_Item_ManaCharge::Start()
{
}

void Skill_Item_ManaCharge::Passive()
{
	if (coolTimeTick <= coolTime && manaStackChargeCount < MaxChargeCount)
	{
		coolTimeTick += Time::DeltaTime();
		if (coolTimeTick > coolTime) {
			coolTimeTick -= coolTime;
			manaStackChargeCount++;
		}
	}
	if (buffSkill == nullptr) {
		buffSkill = new Buff_ItemManaCharge(host);
		host->stat->AddBuff(buffSkill);
	}
	return;
}

void Skill_Item_ManaCharge::Active()
{
	End();
}


void Skill_Item_ManaCharge::End()
{
	Skill::End();
}

Skill* Skill_Item_ManaCharge::Clone()
{
	return new Skill_Item_ManaCharge(nullptr);
}

void Skill_Item_ManaCharge::OnDamaged(Unit* target, Skill* targetSkill, float* damage)
{
	if (dynamic_cast<Minion*>(target) != nullptr)
		target->TakeDamage(5.f);
}

void Skill_Item_ManaCharge::OnTargetFirstHit(Unit* target, Skill* mySkill)
{
	if (buffSkill == nullptr)
		return;

	if (mySkill == host->skillList[(int)SkillIndex::Attack])
		return;

	int a = mySkill->GetHitList()->size();
	if (mySkill->GetHitList()->size() != 1)
		return;

	if (manaStackChargeCount > 0) {
		manaStackChargeCount--;
		manaStack += 4.f;
		buffSkill->modifiers.begin()->value = manaStack;
	}
}
