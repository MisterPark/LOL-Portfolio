#pragma once
#include "Skill.h"
#include "Unit.h"

class Buff_GarenPHealthRegen;
class Skill_Garen_P :
    public Skill
{
public:
    Skill_Garen_P(Unit* _hostUnit);
    virtual ~Skill_Garen_P();

    virtual void Start();
    virtual void Passive();
    virtual void Active();
    virtual void End();

private:
    Buff_GarenPHealthRegen* passiveBuff = nullptr;
    //float reductionTime = 1.f;
    //float reductionValue = 0.3f;

    //float baseShield = 45.f;
    //float growthShield = 25.f;
    //float damageWeight = 0.2f;
};

