#pragma once
#include "Buff.h"
class Buff_ItemWraithStep_P :
    public Buff
{
public:
    Buff_ItemWraithStep_P(Unit* _host);
    virtual ~Buff_ItemWraithStep_P();

    virtual void Update() override;
};

