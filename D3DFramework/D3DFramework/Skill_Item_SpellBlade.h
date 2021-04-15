#pragma once
#include "Skill.h"

class Buff_ItemSpellBlade;
class Skill_Item_SpellBlade : // 광휘의검
    public Skill
{
public:
	Skill_Item_SpellBlade(Unit* _hostUnit);
	virtual ~Skill_Item_SpellBlade();

	virtual void Start() override;
	virtual void Passive() override;
	virtual void Active() override;
	virtual void End() override;
	virtual Skill_Item* Clone() override;

	virtual void OnHit(Unit* target, Skill* mySkill) override;
    virtual void OnOtherSkillStart(Skill* otherSkill) override;

private:
	Buff_ItemSpellBlade* buffSkill = nullptr;
};

