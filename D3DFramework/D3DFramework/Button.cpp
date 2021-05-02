#include "stdafx.h"
#include "Button.h"
#include "Label.h"

Button::Button(const std::wstring& _tag, const Vector2& pos)
	: UI(_tag, pos)
{
	label = new Label();
	AddChild(L"Text", label);
	SetTexture(_tag);
}

Button::~Button()
{
}

void Button::Initialize()
{
	
}

void Button::Release()
{
}

void Button::Update()
{
	UI::Update();
}


void Button::OnHover()
{
	UI::OnHover();

	mesh->SetTexture(hoverTexture);
	SetSizeByTexture();
}

void Button::OnLeave()
{
	UI::OnLeave();
	mesh->SetTexture(originTexture);
	SetSizeByTexture();
}

void Button::OnLButtonDown()
{
	UI::OnLButtonDown();
	mesh->SetTexture(pressedTexture);
	SetSizeByTexture();
	
}

void Button::OnLButtonUp()
{
	UI::OnLButtonUp();
	mesh->SetTexture(originTexture);
	SetSizeByTexture();
}

void Button::OnClick()
{
	UI::OnClick();

}

void Button::OnEnabledChanged()
{
	UI::OnEnabledChanged();
	if (enable == false)
	{
		mesh->SetTexture(disableTexture);
		SetSizeByTexture();
	}
}

void Button::OnTextChanged()
{
	UI::OnTextChanged();
	label->SetText(text);
}

void Button::SetTexture(const wstring& _key)
{
	UI::SetTexture(_key);
	originTexture = _key;
	hoverTexture = _key;
	pressedTexture = _key;
	disableTexture = _key;
}

void Button::SetTextureHover(const wstring& _key)
{
	hoverTexture = _key;
}

void Button::SetTexturePressed(const wstring& _key)
{
	pressedTexture = _key;
}

void Button::SetTextureDisable(const wstring& _key)
{
	disableTexture = _key;
}

void Button::SetLabelSize(int _size)
{
	if (label == nullptr) return;
	label->SetFontSize(_size);
}

void Button::SetLabelPosition(Vector2 _pos)
{
	if (label == nullptr) return;
	label->SetLocation(_pos);
}

void Button::SetLabelAlign(Label::Align _align)
{
	if (label == nullptr) return;
	label->align = _align;
}

void Button::SetLabelVAlign(Label::VAlign _valign)
{
	if (label == nullptr) return;
	label->valign = _valign;
}

void Button::SetLabelColor(D3DCOLOR _color)
{
	if (label == nullptr) return;
	label->SetColor(_color);
}
