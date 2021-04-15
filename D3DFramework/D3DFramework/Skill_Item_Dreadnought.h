#pragma once
#include "Skill.h"

class Buff_ItemDreadnought;

class Skill_Item_Dreadnought : // 망자의 갑옷
    public Skill
{
public:
	Skill_Item_Dreadnought(Unit* _hostUnit);
	virtual ~Skill_Item_Dreadnought();

	virtual void Start() override;
	virtual void Passive() override;
	virtual void Active() override;
	virtual void End() override;
	virtual Skill_Item* Clone() override;


	virtual void OnAttackEnd();

	Buff_ItemDreadnought* buffDreadnought = nullptr;

//private:
	//float passiveTick = 0.f;
	//float passiveStack = 0.f;
};

