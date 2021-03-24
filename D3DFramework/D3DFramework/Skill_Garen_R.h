#pragma once
#include "TargetingSkill.h"
class Skill_Garen_R :
    public TargetingSkill
{
public:
    Skill_Garen_R(Unit* _hostUnit);
    virtual ~Skill_Garen_R();

    virtual void Start();
    virtual void Passive();
    virtual void Active();
    virtual void End();

private:
    float baseDamage = 150.f;
    float growthDamage = 50.f;
    float lostHpWeight = 0.2f;
    float growthLostHpWeight = 0.05f;
};



