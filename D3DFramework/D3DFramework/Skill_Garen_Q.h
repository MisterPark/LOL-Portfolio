#pragma once
#include "Skill.h"
#include "Unit.h"

class Skill_Garen_Q :
    public Skill
{
public:
    Skill_Garen_Q(Unit* _hostUnit);
    virtual ~Skill_Garen_Q();

    virtual void Start();
    virtual void Passive();
    virtual void Active();
    virtual void End();

    virtual void OnHit(Unit* target, Skill* mySkill) override;

private:
    float baseSpeedTime = 1.f;
    float growthSpeedTime = 0.65f;
    float addSpeedPercent = 0.3f;
    float addSpeedValue = 0.f;
    float durationSpeedTime = 0.f;
    float silenceTime = 1.5f;

    float baseDamage = 30.f;
    float growthDamage = 30.f;
    float damageWeight = 1.5f;
};


