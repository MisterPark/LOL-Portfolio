﻿#pragma once
#include "Skill.h"
class Skill_Item_Thorns : //덤불조끼 반사딜
    public Skill
{
public:
	Skill_Item_Thorns(Unit* _hostUnit);
	virtual ~Skill_Item_Thorns();

	virtual void Start();
	virtual void Passive();
	virtual void Active();
	virtual void End();
	virtual void OnDamaged(Unit* target, Skill* targetSkill, float damage) override;
};

