#pragma once
#include "Buff.h"
class Buff_ItemNimble :
    public Buff
{
public:
    Buff_ItemNimble(Unit* _host, float _duration, float _value);
    virtual ~Buff_ItemNimble();

    virtual void Update() override;
};

