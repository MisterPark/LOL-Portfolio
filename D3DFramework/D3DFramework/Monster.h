#pragma once
#include "GameObject.h"

class Monster :
    public GameObject
{
public:
    Monster();
    virtual ~Monster();
    // GameObject을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render() override;

    void Billboard();
};

