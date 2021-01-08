#pragma once
#include "UI.h"
class LoadingBackGround :
    public UI
{
public:
    LoadingBackGround();
    virtual ~LoadingBackGround();
    // UI을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void Release() override;

    virtual void Update() override;
};

