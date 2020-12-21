#pragma once
#include "Champion.h"
class Jinx :
    public Champion
{
public:
    Jinx();
    virtual ~Jinx();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
};

