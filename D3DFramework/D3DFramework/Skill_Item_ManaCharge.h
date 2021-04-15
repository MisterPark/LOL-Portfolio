#pragma once
#include "Skill_Item.h"
#include "Buff_ItemManaCharge.h"
class Skill_Item_ManaCharge :  // 여신의 눈물
    public Skill_Item
{
public:
	Skill_Item_ManaCharge(Unit* _hostUnit);
	virtual ~Skill_Item_ManaCharge();

	virtual void Start() override;
	virtual void Passive() override;
	virtual void Active() override;
	virtual void End() override;
	virtual Skill_Item* Clone() override;

	virtual void OnTargetFirstHit(Unit* target, Skill* mySkill) override;

private:
	Buff_ItemManaCharge* buffSkill = nullptr;
	float manaStack = 0.f;
	int manaStackChargeCount = 0;
};

