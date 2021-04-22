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

    virtual void OnDie() override;
    void OnCollisionEnter(Collider* target);


public:
    MinionAI* ai = nullptr;
    
};

