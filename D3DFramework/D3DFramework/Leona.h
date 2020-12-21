#pragma once
#include "Champion.h"
class Leona :
    public Champion
{
public:
    Leona();
    virtual ~Leona();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
};

