#pragma once
#include "Champion.h"
class Leesin :
    public Champion
{
public:
    Leesin();
    virtual ~Leesin();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
};

