#pragma once
#include "GameObject.h"
class Wall :
    public GameObject
{
public:
    Wall();
    virtual ~Wall();

    // GameObject을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

};

