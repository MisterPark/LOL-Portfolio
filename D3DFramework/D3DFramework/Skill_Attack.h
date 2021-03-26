#pragma once
#include "TargetingSkill.h"
class Skill_Attack :
    public TargetingSkill
{
public:
    Skill_Attack(Unit* _hostUnit);
    virtual ~Skill_Attack();
    virtual void Start() override;
    virtual void Passive() override;
    virtual void Active() override;
    virtual void End() override;

    void AttackCancleToAttack();
protected:
    //bool attackFlag = false;
};

