#pragma once
#include "Buff.h"
class Buff_MissFortuneWAttackSpeed :
    public Buff
{
public:
    Buff_MissFortuneWAttackSpeed(Unit* _host, float _duration, float _value);
    virtual ~Buff_MissFortuneWAttackSpeed();

    virtual void Update() override;

};

