#pragma once
#include "Skill.h"

class Buff_MissFortuneWMoveSpeed;
class Skill_MissFortune_W :
    public Skill
{
public:
    Skill_MissFortune_W(Unit* _hostUnit);
    virtual ~Skill_MissFortune_W();

    virtual void Start();
    virtual void Passive();
    virtual void Active();
    virtual void End();
    virtual void OnDamaged(float damage) override;

private:
    float movementMaxSpeed = 0.45f;
    float activeAttackSpeed = 0.25f;
    float activeAttackSpeedGrowth = 0.15f;
    float activeAttackSpeedTime = 4.f;

    Buff_MissFortuneWMoveSpeed* moveSpeedBuff = nullptr;
    float passiveTick = 0.f;
};

