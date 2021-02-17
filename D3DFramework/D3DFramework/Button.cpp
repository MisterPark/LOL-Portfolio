#include "stdafx.h"
#include "Button.h"


Button::Button()
{
	Initialize();
}

Button::~Button()
{
	Release();
}

void Button::Initialize()
{
	transform->scale = { 1.f,1.f,1.f };
	originScale = transform->scale;
	
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

	if (!isUpScale)
	{
		isUpScale = true;
		transform->scale *= upScaleRatio;

		SoundManager::PlayOverlapSound(L"ButtonOver.wav", SoundChannel::EFFECT, 0.5f);
	}
	
	
}

void Button::OnLeave()
{
	UI::OnLeave();

	if (isUpScale)
	{
		isUpScale = false;
		transform->scale = originScale;
	}
	
}

void Button::OnLButtonDown()
{
	UI::OnLButtonDown();

	if (!isButtonDown)
	{
		isButtonDown = true;
		originPosition = transform->position;
		transform->position.x += 5;
		transform->position.y += 5;
	}
	
}

void Button::OnLButtonUp()
{
	if (isButtonDown)
	{
		isButtonDown = false;
		transform->position = originPosition;
	}
	
	UI::OnLButtonUp();
}

void Button::OnClick()
{
	UI::OnClick();

	SoundManager::PlayOverlapSound(L"Select.wav", SoundChannel::EFFECT, 0.5f);
}
