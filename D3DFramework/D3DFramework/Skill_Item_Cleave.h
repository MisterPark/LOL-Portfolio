#pragma once
#include "Skill.h"
class Skill_Item_Cleave : //티아멧
    public Skill
{
public:
	Skill_Item_Cleave(Unit* _hostUnit);
	virtual ~Skill_Item_Cleave();

	virtual void Start() override;
	virtual void Passive() override;
	virtual void Active() override;
	virtual void End() override;
	virtual Skill* Clone() override;
	virtual void OnHit(Unit* target, Skill* mySkill) override;
};

