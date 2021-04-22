#pragma once
#include "EffectObject.h"
class Effect_Garen_W_Shield :
    public EffectObject
{
public:
    Effect_Garen_W_Shield();
    virtual ~Effect_Garen_W_Shield();

    virtual void PostUpdate() override;
    virtual void Update() override;
private:
};

