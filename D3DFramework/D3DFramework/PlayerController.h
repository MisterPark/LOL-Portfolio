#pragma once
#include "IComponent.h"
class PlayerController :
    public IComponent
{
public:
    PlayerController();
    virtual ~PlayerController();

    virtual void Update() override;
    // IComponent을(를) 통해 상속됨
    virtual IComponent* Clone() override;


};

