#pragma once
#include "EffectObject.h"


class Effect_Red_Buff :
    public EffectObject
{
public:
    Effect_Red_Buff();
    virtual ~Effect_Red_Buff();

    virtual void Update() override;
};

