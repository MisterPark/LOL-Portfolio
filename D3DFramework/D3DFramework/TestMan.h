#pragma once
#include "GameObject.h"
class TestMan :
    public GameObject
{
public:
    TestMan();
    virtual ~TestMan();
    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void OnCollisionEnter(const Collider* target) override;

};

