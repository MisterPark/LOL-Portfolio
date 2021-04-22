#pragma once
#include "EffectObject.h"
class Effect_Garen_R_GroundImpact :
    public EffectObject
{
public:
    Effect_Garen_R_GroundImpact();
    virtual ~Effect_Garen_R_GroundImpact();

    virtual void PostUpdate() override;
    virtual void Update() override;

private:
    float alpha = 1.f;
    float scale = 1.f;
};

