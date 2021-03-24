#pragma once
#include "Skill.h"

class Unit;

class TargetingSkill :
    public Skill
{
public:
    TargetingSkill();
    virtual ~TargetingSkill();

    virtual void Use() override;
    virtual bool InRange() override;

    bool IsTargetInRange();
    bool IsPositionInRange();
};

