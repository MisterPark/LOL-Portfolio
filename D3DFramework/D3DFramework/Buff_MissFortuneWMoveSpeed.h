#pragma once
#include "Buff.h"
class Buff_MissFortuneWMoveSpeed :
    public Buff
{
public:
    Buff_MissFortuneWMoveSpeed(Unit* _host);
    virtual ~Buff_MissFortuneWMoveSpeed();

    virtual void Update() override;

};

