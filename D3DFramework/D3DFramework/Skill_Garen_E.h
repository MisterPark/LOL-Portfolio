#pragma once
#include "Skill.h"
#include "Unit.h"
#include "Buff_GarenEDamage.h"

class Skill_Garen_E :
    public Skill
{
public:
    Skill_Garen_E(Unit* _hostUnit);
    virtual ~Skill_Garen_E();

    virtual void Start();
    virtual void Passive();
    virtual void Active();
    virtual void End();

private:
    float damageTime = 1.f;

    float baseDamage = 4.f;
    float growthDamage = 4.f;
    float damageWeight = 0.32f;
    float growthDamageWeight = 0.02f;

    Buff_GarenEDamage* damageBuff = nullptr;
};


