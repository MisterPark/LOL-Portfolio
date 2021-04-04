#pragma once
#include "Buff.h"
class Buff_MissFortuneESlow :
    public Buff
{
public:
    Buff_MissFortuneESlow(Unit* _host, float _duration, float _value);
    virtual ~Buff_MissFortuneESlow();

    virtual void Update() override;

};

