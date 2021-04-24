#pragma once
#include "EffectObject.h"
class Effect_Garen_Q_Impact :
    public EffectObject
{
public:
    Effect_Garen_Q_Impact();
    virtual ~Effect_Garen_Q_Impact();

    virtual void PostUpdate() override;
    virtual void Update() override;

private:
    float alpha = 1.f;
};

