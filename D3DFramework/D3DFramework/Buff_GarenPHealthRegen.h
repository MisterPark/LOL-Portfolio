﻿#pragma once
#include "Buff.h"
class Buff_GarenPHealthRegen :
    public Buff
{
public:
    Buff_GarenPHealthRegen(Unit* _host, float _duration = INFINITY);
    virtual ~Buff_GarenPHealthRegen();

    virtual void Update() override;
};

