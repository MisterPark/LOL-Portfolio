#pragma once
#include "Buff.h"
class Buff_Item :
    public Buff
{
public:
    Buff_Item(Unit* _host);
    virtual ~Buff_Item();

    virtual void Update();
};

