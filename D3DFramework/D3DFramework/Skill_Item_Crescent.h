#pragma once
#include "Skill.h"
class Skill_Item_Crescent : // 강철 가시 채찍
    public Skill
{
public:
	Skill_Item_Crescent(Unit* _hostUnit);
	virtual ~Skill_Item_Crescent();

	virtual void Start();
	virtual void Passive();
	virtual void Active();
	virtual void End();

private:
	void SkillAttack();

};

