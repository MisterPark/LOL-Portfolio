#pragma once
#include "Champion.h"
class Ahri :
    public Champion
{
public:
    Ahri();
    virtual ~Ahri();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
};

