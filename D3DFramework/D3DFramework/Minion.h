﻿#pragma once
#include "Unit.h"

class MinionFloatingBar;
class MinionAI;

enum class MinionType { Caster, Melee, Siege, Super, End };

class Minion :
    public Unit
{
public:
    Minion();
    virtual ~Minion();

    virtual void OnDeathEnd() override;
    void OnCollisionEnter(Collider* target);
    virtual void Die() override;
    void TakeExp();

public:
    MinionAI* ai = nullptr;
    static list<Minion*> minionList;
};

