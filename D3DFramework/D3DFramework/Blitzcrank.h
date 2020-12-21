#pragma once
#include "Champion.h"
class Blitzcrank :
    public Champion
{
public:
    Blitzcrank();
    virtual ~Blitzcrank();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
};

