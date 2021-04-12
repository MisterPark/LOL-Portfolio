#pragma once
#include "Skill.h"
#include "Unit.h"

class Skill_MissFortune_P :
    public Skill
{
public:
    Skill_MissFortune_P(Unit* _hostUnit);
    virtual ~Skill_MissFortune_P();

    virtual void Start();
    virtual void Passive();
    virtual void Active();
    virtual void End();

    virtual void OnHit(Unit* target) override;

private:
    Unit* lastAttack = nullptr;
};

