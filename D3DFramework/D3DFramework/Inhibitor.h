#pragma once
#include "Building.h"

class TurretFloatingBar;

class Inhibitor :
    public Building
{
public:
    Inhibitor();
    virtual ~Inhibitor();

    virtual void SetTeam(Team _team);

public:
    TurretFloatingBar* bar = nullptr;
};

