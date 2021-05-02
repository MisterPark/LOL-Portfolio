#pragma once
#include "Unit.h"
class Bush :
    public GameObject
{
public:
    Bush();
    virtual ~Bush();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
};

