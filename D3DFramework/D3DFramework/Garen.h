﻿#pragma once
#include "Champion.h"
class Garen :
    public Champion
{
public:
    Garen();
    virtual ~Garen();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void OnAttackBegin() override;
    virtual void OnAttackEnd() override;
    virtual void OnHit(Unit* target, Skill* mySkill) override;
    virtual void Die() override;

    virtual void SkillQAction();
    virtual void SkillWAction();
    virtual void SkillEAction();
    virtual void SkillRAction();

};

