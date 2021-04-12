#pragma once
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

    void OnCollisionEnter(Collider* target);


public:
    MinionFloatingBar* bar = nullptr;
    MinionAI* ai = nullptr;
    
};

