#pragma once
#include "Buff.h"
#include "DamageObject_Garen_E.h"
class Buff_GarenEDamage :
    public Buff
{
public:
    Buff_GarenEDamage(Unit* _host, float _duration, DamageObject_Garen_E* _damageObject);
    virtual ~Buff_GarenEDamage();

    virtual void Update() override;

private:
    DamageObject_Garen_E* damageObject = nullptr;
};

