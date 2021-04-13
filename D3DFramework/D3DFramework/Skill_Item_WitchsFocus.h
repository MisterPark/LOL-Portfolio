#pragma once
#include "Skill_Item.h"

class Buff_ItemWitchsFocus;
class Skill_Item_WitchsFocus :  //추적자의 팔목보호대
    public Skill_Item
{
public:
	Skill_Item_WitchsFocus(Unit* _hostUnit);
	virtual ~Skill_Item_WitchsFocus();

	virtual void Start();
	virtual void Passive();
	virtual void Active();
	virtual void End();
	virtual void OnKilled(Unit* target) override;


	Buff_ItemWitchsFocus* buffWitchsFocus = nullptr;
	int passiveStack = 0;
};

