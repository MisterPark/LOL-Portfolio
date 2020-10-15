#pragma once
#include "GameObject.h"
class Player :
    public GameObject
{

public:
    Player();
    ~Player();



    // GameObject을(를) 통해 상속됨
    virtual void Update() override;

};

