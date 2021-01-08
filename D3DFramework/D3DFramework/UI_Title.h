#pragma once
#include "UI.h"
class UI_Title :
    public UI
{
public:
    UI_Title();
    virtual ~UI_Title();

    virtual void Initialize() override;
    virtual void Release() override;

    virtual void OnHover() override;
    virtual void OnLeave() override;
    virtual void OnLButtonDown() override;
    virtual void OnLButtonUp() override;
    virtual void OnClick() override;
    
};

