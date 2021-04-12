#pragma once
#include "EffectObject.h"
class Effect_Baron_Buff :
    public EffectObject
{
public:
    Effect_Baron_Buff();
    virtual ~Effect_Baron_Buff();

    virtual void Update() override;
};

