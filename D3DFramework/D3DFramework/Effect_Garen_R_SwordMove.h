#pragma once
#include "EffectObject.h"
class Effect_Garen_R_SwordMove :
    public EffectObject
{
public:
    Effect_Garen_R_SwordMove();
    virtual ~Effect_Garen_R_SwordMove();

    virtual void PostUpdate() override;
    virtual void Update() override;
};

