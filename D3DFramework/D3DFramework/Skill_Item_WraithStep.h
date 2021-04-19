#pragma once
#include "Skill.h"

class Buff_Item_WraithStep_P;
class Skill_Item_WraithStep : // 요우무의 유령검
    public Skill
{
public:
	Skill_Item_WraithStep(Unit* _hostUnit);
	virtual ~Skill_Item_WraithStep();

	virtual void Start();
	virtual void Passive();
	virtual void Active();
	virtual void End();
	virtual Skill* Clone() override;

	virtual void OnHit(Unit* target, Skill* mySkill) override;
    virtual void OnDamaged(Unit* target, Skill* targetSkill, float damage) override;

private:
	float passiveTick = 0.f;
	Buff_Item_WraithStep_P* passiveBuff = nullptr;
};

