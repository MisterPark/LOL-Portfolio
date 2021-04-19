#pragma once
#include "Buff.h"
class Buff_Item_WraithStep :
    public Buff
{
public:
    Buff_Item_WraithStep(Unit* _host, float _duration, float _value);
    virtual ~Buff_Item_WraithStep();

    virtual void Update() override;
};

