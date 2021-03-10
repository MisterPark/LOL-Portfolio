#pragma once
#include "Buff.h"

class Buff_GarenWReduction : 
	public Buff
{
public:
    Buff_GarenWReduction(Unit* _host, float _duration, float _value);
    virtual ~Buff_GarenWReduction();

    virtual void Update() override;

};

