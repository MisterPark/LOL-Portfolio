#pragma once
#include "Buff.h"
class Buff_ItemManaCharge :
    public Buff
{
public:
    Buff_ItemManaCharge(Unit* _host);
    virtual ~Buff_ItemManaCharge();

    virtual void Update() override;
};

