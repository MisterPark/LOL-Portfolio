#pragma once
#include "Skill.h"
class Skill_Item_Precision : // 절정의 화살
    public Skill
{
public:
	Skill_Item_Precision(Unit* _hostUnit);
	virtual ~Skill_Item_Precision();

	virtual void Start() override;
	virtual void Passive() override;
	virtual void Active() override;
	virtual void End() override;
	virtual Skill* Clone() override;

	virtual void OnDamaged(Unit* target, Skill* targetSkill, float damage);

};

