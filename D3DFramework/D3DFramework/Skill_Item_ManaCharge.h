#pragma once
#include "Skill.h"
#include "Buff_ItemManaCharge.h"
class Skill_Item_ManaCharge :  // 여신의 눈물
    public Skill
{
public:
	Skill_Item_ManaCharge(Unit* _hostUnit);
	virtual ~Skill_Item_ManaCharge();

	virtual void Start();
	virtual void Passive();
	virtual void Active();
	virtual void End();
	virtual void OnTargetFirstHit(Unit* target, Skill* mySkill);

private:
	Buff_ItemManaCharge* buffSkill = nullptr;
	float manaStack = 0.f;
	int manaStackChargeCount = 0;
};

