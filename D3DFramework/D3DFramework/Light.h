#pragma once
#include "GameObject.h"
class Light :
    public GameObject
{
public:
    Light();
    virtual ~Light();
    // GameObject을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render() override;

private:
    D3DLIGHT9 lightInfo;
    UINT index;
};

