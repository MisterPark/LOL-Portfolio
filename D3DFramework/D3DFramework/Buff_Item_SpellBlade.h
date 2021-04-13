#pragma once
#include "Buff_OnHit.h"
class Buff_ItemSpellBlade :
    public Buff_OnHit
{
public:
    Buff_ItemSpellBlade(Unit* _host, float _duration, float _basicDamage, DamageKind _damageKind);
    virtual ~Buff_ItemSpellBlade();

    virtual void Update() override;

};

