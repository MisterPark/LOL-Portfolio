#include "stdafx.h"
#include "Button.h"


Button::Button(const std::wstring& _tag, const Vector2& pos)
	: UI(_tag, pos)
{
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
	//SoundManager::PlayOverlapSound(L"ButtonOver.wav", SoundChannel::EFFECT, 0.5f);
	
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

	//SoundManager::PlayOverlapSound(L"Select.wav", SoundChannel::EFFECT, 0.5f);
}

void Button::OnEnabledChanged()
{
	UI::OnEnabledChanged();
	if (isEnable == false)
	{
		mesh->SetTexture(disableTexture);
		SetSizeByTexture();
	}
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
