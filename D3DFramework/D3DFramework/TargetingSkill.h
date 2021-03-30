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

    bool GetGroundClick() { return groundClick; }

    bool IsTargetInRange();
    bool IsPositionInRange();

protected:
    // 유닛클릭이 가능할때, 어택땅 기능을 쓸지 말지
    bool groundClick = true;
};

