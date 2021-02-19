#pragma once
#include "UI.h"
#include "Label.h"

class Button :
    public UI
{
public:
    Button(const std::wstring& _tag, const Vector2& pos);
    virtual ~Button();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void OnHover() override;
    virtual void OnLeave() override;
    virtual void OnLButtonDown() override;
    virtual void OnLButtonUp() override;
    virtual void OnClick() override;
    virtual void OnEnabledChanged() override;
    virtual void OnTextChanged() override;

    virtual void SetTexture(const wstring& _key);
    void SetTextureHover(const wstring& _key);
    void SetTexturePressed(const wstring& _key);
    void SetTextureDisable(const wstring& _key);

    void SetLabelSize(int _size);
    void SetLabelPosition(Vector2 _pos);
    void SetLabelAlign(Label::Align _align);
    void SetLabelVAlign(Label::VAlign _valign);
    void SetLabelColor(D3DCOLOR _color);

public:

private:
    wstring originTexture = L"";
    wstring hoverTexture = L"";
    wstring pressedTexture = L"";
    wstring disableTexture = L"";
    
    Label* label = nullptr;
};

