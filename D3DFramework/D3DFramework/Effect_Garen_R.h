#pragma once
#include "EffectObject.h"
class Effect_Garen_R :
    public EffectObject
{
public:
    Effect_Garen_R();
    virtual ~Effect_Garen_R();

    virtual void PostUpdate() override;
    virtual void Update() override;
};

