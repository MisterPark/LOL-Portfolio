#pragma once
#include "Skill.h"
class Skill_Item_Immolate :  // 바미의 불씨
    public Skill
{
public:
	Skill_Item_Immolate(Unit* _hostUnit);
	virtual ~Skill_Item_Immolate();

	virtual void Start();
	virtual void Passive();
	virtual void Active();
	virtual void End();
	virtual Skill* Clone() override;

private:
	void SkillAttack();
};

