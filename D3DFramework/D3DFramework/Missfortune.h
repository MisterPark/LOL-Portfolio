#pragma once
#include "Champion.h"
class Missfortune :
    public Champion
{
public:
    Missfortune();
    virtual ~Missfortune();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Die() override;

    virtual void OnHit(Unit* target, Skill* mySkill) override;
};

