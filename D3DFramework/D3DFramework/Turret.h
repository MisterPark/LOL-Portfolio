#pragma once
#include "Building.h"

class TurretFloatingBar;

class Turret :
    public Building
{
public:
    Turret();
    virtual ~Turret();

    virtual void SetTeam(Team _team);

public:
    TurretFloatingBar* bar = nullptr;
};

