#pragma once
#include "UI.h"
class UI_Spell :
    public UI
{
public:
    UI_Spell();
    virtual ~UI_Spell();

    virtual void Initialize() override;
    virtual void Release() override;
};

