#pragma once
#include "Buff.h"
class Buff_HealMoveSpeed :
    public Buff
{
public:
    Buff_HealMoveSpeed(Unit* _host);
    virtual ~Buff_HealMoveSpeed();

    virtual void Update() override;
};

