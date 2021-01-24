#pragma once
#include "Unit.h"

class MinionFloatingBar;

class Monster : public Unit
{
public:
    Monster();
    virtual ~Monster();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;


public:
    MinionFloatingBar* bar = nullptr;
};
