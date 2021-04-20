#pragma once
#include "Skill.h"
class Skill_Item_HealthPotion :
    public Skill
{
public:
	Skill_Item_HealthPotion(Unit* _hostUnit);
	virtual ~Skill_Item_HealthPotion();

	virtual void Start();
	virtual void Passive();
	virtual void Active();
	virtual void End();
	virtual Skill* Clone() override;


};

