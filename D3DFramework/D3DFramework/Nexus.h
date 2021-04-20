﻿#pragma once
#include "Building.h"
class Nexus :
    public Building
{
public:
    Nexus();
    virtual ~Nexus();

    virtual void OnDamaged(Unit* target, Skill* targetSkill, float* damage) override;
};

