#pragma once
#include "Buff.h"
class Buff_Item_WraithStep_P :
    public Buff
{
public:
    Buff_Item_WraithStep_P(Unit* _host);
    virtual ~Buff_Item_WraithStep_P();

    virtual void Update() override;
};

