#pragma once
#include "Buff_OnHit.h"
class Buff_Item_SteelTipped :
    public Buff_OnHit
{
public:
    Buff_Item_SteelTipped(Unit* _host, float _basicDamage, DamageKind _damageKind);
    virtual ~Buff_Item_SteelTipped();

    virtual void Update() override;
};

