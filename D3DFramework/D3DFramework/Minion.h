#pragma once
#include "Unit.h"

class MinionFloatingBar;

class Minion :
    public Unit
{
public:
    Minion();
    virtual ~Minion();


public:
    MinionFloatingBar* bar = nullptr;
};

