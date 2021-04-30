#pragma once
#include "GameObject.h"

class ArrowPointer : public GameObject
{
private:
    ArrowPointer();
    virtual ~ArrowPointer();

public:
    static ArrowPointer* GetInstance();
    static void DestroyInstance();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
};

