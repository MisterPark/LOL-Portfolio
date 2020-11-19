#pragma once
#include "IComponent.h"
class Collider :
    public IComponent
{
    // IComponent을(를) 통해 상속됨
    virtual IComponent* Clone() override;
};

