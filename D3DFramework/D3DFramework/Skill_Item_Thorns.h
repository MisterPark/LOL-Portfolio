#pragma once
#include "Skill.h"
class Skill_Item_Thorns : //덤불조끼 반사딜
    public Skill
{
public:
	Skill_Item_Thorns(Unit* _hostUnit);
	virtual ~Skill_Item_Thorns();

	virtual void Start() override;
	virtual void Passive() override;
	virtual void Active() override;
	virtual void End() override;
	virtual Skill_Item* Clone() override;

	virtual void OnDamaged(Unit* target, Skill* targetSkill, float damage) override;
};

