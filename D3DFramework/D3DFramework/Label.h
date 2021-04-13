#pragma once
#include "UI.h"


class Label :
    public UI
{
public:
    enum class Align
    {
        Left,
        Center,
        Right
    };
    enum class VAlign
    {
        Top,
        Middle,
        Bottom
    };
public:

    Label();
    Label(int fontSize);
    virtual ~Label();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    std::wstring GetText();
    std::wstring GetDrawText();
    virtual void SetText(const wstring& _text) override;
    virtual void SetText(int _value);
    virtual void SetText(LPCTSTR pszStr, ...);

    void SetFontSize(int _fontsize);

    D3DCOLOR GetColor();
    D3DCOLOR GetShadowColor();
    D3DCOLOR GetOutlineColor();
    void SetColor(unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b);
    void SetColor(D3DCOLOR _color);
    void SetShadowColor(unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b);
    void SetOutlineColor(unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b);

    void SetWidthLimit(int _limit);
    void AdjustTextByWidthLimit();
    int GetTextWidth();
    int GetTextHeight();
    int GetDrawTextWidth();
    int GetDrawTextHeight();
    bool IsLineAlignment();

private:
    void MakeFont(int fontSize = 20);

public:
    Label::Align  align  = Label::Align::Left;
    Label::VAlign valign = Label::VAlign::Top;
    bool outline = false;
    bool shadow = true;

    LPD3DXFONT        pFont = nullptr;
    LPD3DXSPRITE      pSprite = nullptr;
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    RECT rcDraw = {};

private:
    wstring text;
    wstring drawText;
    D3DCOLOR foreColor = D3DCOLOR_ARGB(255, 254, 254, 254);
    D3DCOLOR shadowColor = D3DCOLOR_ARGB(255, 0, 0, 0);
    D3DCOLOR outlineColor = D3DCOLOR_ARGB(255, 0, 0, 0);

    int widthLimit = 0;
    bool lineAlignment = false; // AdjustTextByWidthLimit 함수로 인한 drawText 강제 개행 여부
    
};

