#pragma once
#include "Skill_Item.h"

class Buff_ItemWitchsFocus;
class Skill_Item_WitchsFocus :  //추적자의 팔목보호대
    public Skill_Item
{
public:
	Skill_Item_WitchsFocus(Unit* _hostUnit);
	virtual ~Skill_Item_WitchsFocus();

	virtual void Start() override;
	virtual void Passive() override;
	virtual void Active() override;
	virtual void End() override;
	virtual Skill_Item* Clone() override;

	virtual void OnKilled(Unit* target) override;

	Buff_ItemWitchsFocus* buffWitchsFocus = nullptr;
	int passiveStack = 0;
};

