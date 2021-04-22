#pragma once
#include "EffectObject.h"
class Effect_Garen_R_GroundDecal :
    public EffectObject
{
public:
    Effect_Garen_R_GroundDecal();
    virtual ~Effect_Garen_R_GroundDecal();

    virtual void PostUpdate() override;
    virtual void Update() override;

private:
    float alpha = 1.f;
};

