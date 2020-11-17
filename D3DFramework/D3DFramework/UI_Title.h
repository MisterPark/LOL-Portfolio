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

    virtual void UpdateUI() override;

    virtual void OnHover() override;
    virtual void OnLeave() override;
    virtual void OnLButtonDown() override;
    virtual void OnLButtonUp() override;
    virtual void OnClick() override;

    virtual void SetTexture(TextureKey _key);
    
};

