#pragma once
#include "Skill.h"
class Skill_Item_Nimble :  // 온기가 필요한 자의 도끼
    public Skill
{
public:
	Skill_Item_Nimble(Unit* _hostUnit);
	virtual ~Skill_Item_Nimble();

	virtual void Start();
	virtual void Passive();
	virtual void Active();
	virtual void End();
	virtual void OnHit(Unit* target, Skill* mySkill) override;
};

