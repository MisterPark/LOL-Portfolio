#pragma once
#include "Buff.h"
class Buff_ItemWitchsFocus :
    public Buff
{
public:
    Buff_ItemWitchsFocus(Unit* _host);
    virtual ~Buff_ItemWitchsFocus();

    virtual void Update() override;
};

