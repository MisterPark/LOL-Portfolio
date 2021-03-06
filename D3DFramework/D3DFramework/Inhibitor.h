﻿#pragma once
#include "Building.h"

class TurretFloatingBar;

class Inhibitor :
    public Building
{
public:
    Inhibitor();
    virtual ~Inhibitor();

    virtual void OnDeathBegin(Unit* _lastAttacker) override;

    virtual void SetTeam(Team _team);
    virtual void Die() override;
    virtual void OnRespawn() override;
};

