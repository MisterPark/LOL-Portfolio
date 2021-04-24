#pragma once
#include "EffectObject.h"
class Effect_Garen_R_Dome :
    public EffectObject
{
public:
    Effect_Garen_R_Dome();
    virtual ~Effect_Garen_R_Dome();

    virtual void PostUpdate() override;
    virtual void Update() override;

private:
    float alpha = 1.f;
    float scale = 1.f;
};

