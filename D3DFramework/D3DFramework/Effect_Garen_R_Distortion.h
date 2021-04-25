#pragma once
#include "EffectObject.h"
class Effect_Garen_R_Distortion :
    public EffectObject
{
public:
    Effect_Garen_R_Distortion();
    virtual ~Effect_Garen_R_Distortion();

    virtual void PostUpdate() override;
    virtual void Update() override;

private:
    float opacity = 1.f;
    float scale = 1.f;
};

