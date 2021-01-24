#pragma once
#include "Unit.h"
class Building :
    public Unit
{
public:
    Building();
    virtual ~Building();

    virtual void OnCollisionEnter(Collider* target);
};

