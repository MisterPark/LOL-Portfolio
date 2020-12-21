#pragma once
#include "Champion.h"
class Diana :
    public Champion
{
public:
    Diana();
    virtual ~Diana();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
};

