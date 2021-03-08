#pragma once
#include "Buff.h"
class Buff_GarenQHaste :
    public Buff
{
public:
    Buff_GarenQHaste(Unit* _host, float _duration);
    virtual ~Buff_GarenQHaste();

    virtual void Update() override;

};

