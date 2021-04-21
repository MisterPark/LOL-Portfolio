#pragma once
#include "Monster.h"
class Scuttleracer :
    public Monster
{
public:
    enum class ScuttlePos { North, South, END };
public:
    Scuttleracer();
    virtual ~Scuttleracer();

    void SetAI(ScuttlePos _scuttlePos);
};

