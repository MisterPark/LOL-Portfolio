#pragma once
#include "Unit.h"


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
};

