#pragma once
#include "Skill_Item.h"
class Skill_Item_Cleave : //티아멧
    public Skill_Item
{
public:
	Skill_Item_Cleave(Unit* _hostUnit);
	virtual ~Skill_Item_Cleave();

	virtual void Start();
	virtual void Passive();
	virtual void Active();
	virtual void End();
	virtual void OnHit(Unit* target, Skill* mySkill) override;
};

