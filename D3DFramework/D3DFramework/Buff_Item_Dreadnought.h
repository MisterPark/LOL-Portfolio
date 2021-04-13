#pragma once
#include "Buff_OnHit.h"

class Skill_Item_Dreadnought;
class Buff_ItemDreadnought :
    public Buff_OnHit
{
public:
    Buff_ItemDreadnought(Unit* _host, Skill_Item_Dreadnought* _hostSkill, float _duration, float _basicDamage, float _weightDamage, DamageKind _damageKind);
    virtual ~Buff_ItemDreadnought();

    virtual void Update() override;

public:
    float skillStack = 0.f;
    float skillTick = 0.f;

};

