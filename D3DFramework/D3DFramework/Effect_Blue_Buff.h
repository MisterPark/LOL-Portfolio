#pragma once
#include "EffectObject.h"
class Effect_Blue_Buff :
    public EffectObject
{
public:
    Effect_Blue_Buff();
    virtual ~Effect_Blue_Buff();

    virtual void Update() override;
};

