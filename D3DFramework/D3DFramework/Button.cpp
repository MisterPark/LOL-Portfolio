#include "stdafx.h"
#include "Button.h"


Button::Button()
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

	UI::SetTexture(hoverTexture);
	//SoundManager::PlayOverlapSound(L"ButtonOver.wav", SoundChannel::EFFECT, 0.5f);
	
}

void Button::OnLeave()
{
	UI::OnLeave();
	UI::SetTexture(originTexture);
}

void Button::OnLButtonDown()
{
	UI::OnLButtonDown();
	UI::SetTexture(pressedTexture);
	
}

void Button::OnLButtonUp()
{
	UI::OnLButtonUp();
	UI::SetTexture(originTexture);
}

void Button::OnClick()
{
	UI::OnClick();

	//SoundManager::PlayOverlapSound(L"Select.wav", SoundChannel::EFFECT, 0.5f);
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
