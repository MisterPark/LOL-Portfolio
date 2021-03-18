#pragma once
#include "Buff.h"
class Buff_GarenWPassive :
    public Buff
{
public:
    Buff_GarenWPassive(Unit* _host);
    virtual ~Buff_GarenWPassive();

    virtual void Update() override;

};

