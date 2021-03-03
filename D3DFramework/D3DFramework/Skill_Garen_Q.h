#pragma once
#include "Skill.h"
class Skill_Garen_Q :
    public Skill
{
    Skill_Garen_Q();
    virtual ~Skill_Garen_Q();

    virtual void Start();
    virtual void Update();
    virtual void End();

private:
    float baseSpeedTime = 1.f;
    float growthSpeedTime = 0.65f;
    float addSpeedPercent = 30.f;
    float addSpeedValue = 0.f;
    float durationSpeedTime = 0.f;
    float silenceTime = 1.5f;

    float baseDamage = 30.f;
    float growthDamage = 30.f;
    float damageWeight = 1.5f;
};


