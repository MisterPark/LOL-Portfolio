#pragma once
#include "UI.h"
class Button :
    public UI
{
public:
    Button();
    virtual ~Button();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void OnHover() override;
    virtual void OnLeave() override;
    virtual void OnLButtonDown() override;
    virtual void OnLButtonUp() override;
    virtual void OnClick() override;

    virtual void SetTexture(const wstring& _key);
    void SetTextureHover(const wstring& _key);
    void SetTexturePressed(const wstring& _key);
    void SetTextureDisable(const wstring& _key);

private:
    wstring originTexture = L"";
    wstring hoverTexture = L"";
    wstring pressedTexture = L"";
    wstring disableTexture = L"";
};

