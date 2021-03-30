#pragma once
#include "GameObject.h"

class EffectObject :
    public GameObject
{
public:
    EffectObject();
    virtual ~EffectObject();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
};

