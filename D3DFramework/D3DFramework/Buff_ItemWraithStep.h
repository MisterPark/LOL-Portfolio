#pragma once
#include "Buff.h"
class Buff_ItemWraithStep :
    public Buff
{
public:
    Buff_ItemWraithStep(Unit* _host, float _duration, float _value);
    virtual ~Buff_ItemWraithStep();

    virtual void Update() override;
};

