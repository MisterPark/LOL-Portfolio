#pragma once
#include "GameObject.h"
class Unit :
    public GameObject
{
public:
    Unit();
    virtual ~Unit();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;


};

