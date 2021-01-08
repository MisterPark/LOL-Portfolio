#pragma once
#include "UI.h"
class Panel :
    public UI
{
public:
    Panel();
    virtual ~Panel();
    // UI을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void Release() override;

};

