#pragma once
#include "GameObject.h"
class NavMeshMap :
    public GameObject
{
public:
    NavMeshMap();
    virtual ~NavMeshMap();

    // GameObject을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
};

