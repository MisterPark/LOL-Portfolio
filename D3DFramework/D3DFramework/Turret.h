﻿#pragma once
#include "Building.h"

class TurretFloatingBar;

class Turret : public Building
{
public:
    Turret();
    virtual ~Turret();
    
    virtual void Update() override;

    virtual void OnDeathBegin(Unit* _lastAttacker) override;

    virtual void SetTeam(Team _team);
    virtual void Die() override;
    virtual void DeadAction()override;
    virtual void AttackAction() override;
    virtual void CounterAttack()override;
    virtual void IdleAction()override;
    virtual void MoveAction()override;


public:
    Vector3 offsetPos;
    bool breakEffectFlag = false;

    float breakDist = 0.f;
    float breakHeight = 2.f;
};

