#pragma once
#include "Buff.h"
class Buff_ItemStat :
    public Buff
{
public:
    Buff_ItemStat(Unit* _host);
    virtual ~Buff_ItemStat();

    virtual void Update();
};

