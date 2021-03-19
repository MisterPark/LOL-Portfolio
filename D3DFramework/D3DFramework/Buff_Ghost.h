#pragma once
#include "Buff.h"
class Buff_Ghost :
    public Buff
{
public:
    Buff_Ghost(Unit* _host, float _duration, float _value);
    virtual ~Buff_Ghost();

    virtual void Update() override;

private:
    float movementSpeed_Init = 0.f;
};

