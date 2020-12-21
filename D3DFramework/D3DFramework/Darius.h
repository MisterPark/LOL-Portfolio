#pragma once
#include "Champion.h"
class Darius :
    public Champion
{
public:
    Darius();
    virtual ~Darius();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
};

