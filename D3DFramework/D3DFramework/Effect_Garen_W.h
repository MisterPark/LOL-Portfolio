#pragma once
#include "EffectObject.h"
class Effect_Garen_W :
    public EffectObject
{
public:
    Effect_Garen_W();
    virtual ~Effect_Garen_W();

    virtual void PostUpdate() override;

private:
    float offset = 0.f;
};

