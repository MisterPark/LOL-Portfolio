#pragma once
#include "Skill.h"
#include "Unit.h"

class Skill_Garen_W :
    public Skill
{
public:
    Skill_Garen_W(Unit* _hostUnit);
    virtual ~Skill_Garen_W();

    virtual void Start();
    virtual void Passive();
    virtual void Active();
    virtual void End();

private:
    float reductionTime = 1.f;
    float reductionValue = 0.3f;

    float baseShield = 45.f;
    float growthShield = 25.f;
    float damageWeight = 0.2f;
};


