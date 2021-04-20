#pragma once
#include "Skill.h"
#include "Buff_Item_ManaCharge.h"
class Skill_Item_ManaCharge :  // 여신의 눈물
    public Skill
{
public:
	Skill_Item_ManaCharge(Unit* _hostUnit);
	virtual ~Skill_Item_ManaCharge();

	virtual void Start() override;
	virtual void Passive() override;
	virtual void Active() override;
	virtual void End() override;
	virtual Skill* Clone() override;

	virtual void OnDamaged(Unit* target, Skill* targetSkill, float* damage);
	virtual void OnTargetFirstHit(Unit* target, Skill* mySkill) override;

private:
	Buff_ItemManaCharge* buffSkill = nullptr;
	float manaStack = 0.f;
	int manaStackChargeCount = 0;
};

