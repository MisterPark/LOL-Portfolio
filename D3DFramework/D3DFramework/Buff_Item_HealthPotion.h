#pragma once
#include "Buff.h"
class Buff_Item_HealthPotion :
    public Buff
{
public:
    Buff_Item_HealthPotion(Unit* _host, float _duration, float _value);
    virtual ~Buff_Item_HealthPotion();

    virtual void Update() override;

private:
    float healValue = 0.f;
};

