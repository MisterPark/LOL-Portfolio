#pragma once
#include "Buff.h"
class Buff_GarenEArmorDec :
    public Buff
{
public:
    Buff_GarenEArmorDec(Unit* _host, float _duration);
    virtual ~Buff_GarenEArmorDec();

    virtual void Update() override;

};

