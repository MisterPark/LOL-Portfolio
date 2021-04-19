#pragma once
#include "EffectObject.h"
class Effect_Garen_E :
    public EffectObject
{
public:
    Effect_Garen_E();
    virtual ~Effect_Garen_E();

    virtual void PostUpdate() override;
};

