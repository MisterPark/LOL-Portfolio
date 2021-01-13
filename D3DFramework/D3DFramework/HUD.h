#pragma once
#include "UI.h"

class HUD :
    public UI
{
    // UI을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void Release() override;
};

