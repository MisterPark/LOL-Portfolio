#pragma once
#include "Champion.h"
class Jax :
    public Champion
{
public:
    Jax();
    virtual ~Jax();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
};

