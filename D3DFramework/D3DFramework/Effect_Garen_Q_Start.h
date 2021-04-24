#pragma once
#include "EffectObject.h"
class Effect_Garen_Q_Start :
    public EffectObject
{
public:
    Effect_Garen_Q_Start();
    virtual ~Effect_Garen_Q_Start();

    virtual void PostUpdate() override;
    virtual void Update() override;

private:
    float alpha = 1.f;
    float scale = 1.f;
};

