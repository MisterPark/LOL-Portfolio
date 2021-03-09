#pragma once
#include "Buff_OnHit.h"
class Buff_GarenQAttack :
    public Buff_OnHit
{
public:
    Buff_GarenQAttack(Unit* _host, float _duration, float _basicDamage, float _weightDamage);
    virtual ~Buff_GarenQAttack();

    virtual void Update() override;
};

