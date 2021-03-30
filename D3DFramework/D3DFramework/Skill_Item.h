#pragma once
#include "Skill.h"
class Skill_Item :
    public Skill
{
public:
	Skill_Item();
	virtual ~Skill_Item();

	virtual void Start() = 0;
	virtual void Passive() = 0;
	virtual void Active() = 0;
	virtual void End() = 0;
};

