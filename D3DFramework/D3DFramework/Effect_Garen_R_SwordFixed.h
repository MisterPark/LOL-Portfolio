#pragma once
#include "EffectObject.h"
class Effect_Garen_R_SwordFixed :
    public EffectObject
{
public:
    Effect_Garen_R_SwordFixed();
    virtual ~Effect_Garen_R_SwordFixed();

    virtual void PostUpdate() override;
    virtual void Update() override;

private:
    float swordalpha = 1.f;
    float effectalpha = 1.f;
};

