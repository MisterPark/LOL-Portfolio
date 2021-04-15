#pragma once
#include "Skill.h"

class Buff_ItemWraithStep_P;
class Skill_Item_WraithStep :
    public Skill
{
public:
	Skill_Item_WraithStep(Unit* _hostUnit);
	virtual ~Skill_Item_WraithStep();

	virtual void Start();
	virtual void Passive();
	virtual void Active();
	virtual void End();
	virtual void OnHit(Unit* target, Skill* mySkill) override;
    virtual void OnDamaged(Unit* target, Skill* targetSkill, float damage) override;

private:
	float passiveTick = 0.f;
	Buff_ItemWraithStep_P* passiveBuff = nullptr;
};

