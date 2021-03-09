#pragma once
#include "Buff.h"
class Buff_GarenQAttack :
    public Buff
{
public:
    Buff_GarenQAttack(Unit* _host, float _duration);
    virtual ~Buff_GarenQAttack();

    virtual void Update() override;
};

