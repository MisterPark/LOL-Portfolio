#pragma once
#include "Skill_Item.h"

class Buff_ItemSpellBlade;
class Skill_Item_SpellBlade : // 광휘의검
    public Skill_Item
{
public:
	Skill_Item_SpellBlade(Unit* _hostUnit);
	virtual ~Skill_Item_SpellBlade();

	virtual void Start();
	virtual void Passive();
	virtual void Active();
	virtual void End();
	virtual void OnHit(Unit* target, Skill* mySkill) override;
    virtual void OnOtherSkillStart(Skill* otherSkill) override;

private:
	Buff_ItemSpellBlade* buffSkill = nullptr;
};

