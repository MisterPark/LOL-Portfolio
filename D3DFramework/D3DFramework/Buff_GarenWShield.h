#pragma once
#include "Buff.h"

class Buff_GarenWShield :
    public Buff
{
public:
    Buff_GarenWShield(Unit* _host, float _duration, float _value);
    virtual ~Buff_GarenWShield();

    virtual void Update() override;

};

