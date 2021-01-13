#pragma once
#include "Unit.h"

class FloatingBar;

class Champion :
    public Unit
{
public:

    Champion();
    virtual ~Champion();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;


public:
    FloatingBar* bar = nullptr;
};

