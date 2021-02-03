#pragma once
#include "Building.h"

class TurretFloatingBar;

class Turret : public Building
{
public:
    Turret();
    virtual ~Turret();
    
    virtual void Update() override;


    virtual void SetTeam(Team _team);

public:
    TurretFloatingBar* bar = nullptr;
    Vector3 offsetPos;
    bool breakEffectFlag = false;

    float breakDist = 0.f;
    float breakHeight = 2.f;
};

