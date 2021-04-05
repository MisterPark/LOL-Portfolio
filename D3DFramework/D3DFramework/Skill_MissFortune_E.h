#pragma once
#include "TargetingSkill.h"
class Skill_MissFortune_E :
    public TargetingSkill
{
public:
    Skill_MissFortune_E(Unit* _hostUnit);
    virtual ~Skill_MissFortune_E();

    virtual void Use() override;
    virtual bool InRange() override;

    virtual void Start();
    virtual void Passive();
    virtual void Active();
    virtual void End();

private:
    float startTime = 0.5f;
    float damageTime = 2.f;

    float baseDamage = 45.f;
    float growthDamage = 35.f;
    float damageWeight = 0.8f;
    float baseSlow = 0.35f;
    float growthSlow = 0.05f;
    
};

