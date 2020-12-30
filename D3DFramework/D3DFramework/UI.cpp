#include "stdafx.h"
#include "UI.h"
#include "Rectangle.h"

UI::UI()
{
	
}

UI::~UI()
{
}

void UI::Update()
{
	UpdateUI();
	UpdateEvent();
	GameObject::Update();
}

void UI::Render()
{
	RenderManager::DrawUI(textureKey, *transform, 0);

	if (textRenderFlag)
	{
		Vector3 pos = transform->position + textOffsetPosition;
		RenderManager::DrawFont(text, pos.x, pos.y, D3DCOLOR_XRGB(0, 0, 0));
	}
}

void UI::UpdateEvent()
{
	Vector3 cursorPos = Cursor::GetMousePos();

	// Hover & Leave
	if (cursorPos.x > transform->position.x &&
		cursorPos.x < transform->position.x + width &&
		cursorPos.y > transform->position.y &&
		cursorPos.y < transform->position.y + height) 
	{
		if (isHover == false)
		{
			OnHover();
		}
		isLeave = false;
		isHover = true;
		
	}
	else
	{
		if (isLeave == false)
		{
			OnLeave();
			
		}
		isHover = false;
		isLeave = true;
	}

	if (InputManager::GetMouseLButtonDown())
	{
		if (isHover)
		{
			isLButtonDown = true;
			OnLButtonDown();
		}
		
	}
	if (InputManager::GetMouseLButtonUp())
	{
		if (isHover)
		{
			OnLButtonUp();
			if (isLButtonDown)
			{
				OnClick();
			}
		}
		isLButtonDown = false;
	}
	if (InputManager::GetMouseRButtonDown())
	{
		if (isHover)
		{
			isRButtonDown = true;
			OnRButtonDown();
		}
	}
	if (InputManager::GetMouseRButtonUp())
	{
		if (isHover)
		{
			OnRButtonUp();
		}
		isRButtonDown = false;
	}

	if (text.compare(oldText) != 0)
	{
		oldText = text;
		OnChangedText();
	}
}

void UI::ClearEvent()
{
	isHover = false;
	isLeave = false;
	isLButtonDown = false;
	isRButtonDown = false;
}

void UI::OnHover()
{
	if (Hover != nullptr)
	{
		Hover();
	}
}

void UI::OnLeave()
{
	if (Leave != nullptr)
	{
		Leave();
	}
}

void UI::OnLButtonDown()
{
	if (LButtonDown != nullptr)
	{
		LButtonDown();
	}
}

void UI::OnLButtonUp()
{
	if (LButtonUp != nullptr)
	{
		LButtonUp();
	}
}

void UI::OnRButtonDown()
{
	if (RButtonDown != nullptr)
	{
		RButtonDown();
	}
}

void UI::OnRButtonUp()
{
	if (RButtonUp != nullptr)
	{
		RButtonUp();
	}
}

void UI::OnClick()
{
	if (Click != nullptr)
	{
		Click();
	}
}

void UI::OnChangedText()
{
	if (ChangedText != nullptr)
	{
		ChangedText();
	}
}

void UI::SetSize(int w, int h)
{

	width = w;
	height = h;
}

void UI::SetTexture(const wstring& _key)
{
	textureKey = _key;

	Texture* texture = RenderManager::GetTexture(textureKey);
	if (texture != nullptr)
	{
		width = int(transform->scale.x * texture->GetSpriteWidth());
		height = int(transform->scale.y * texture->GetSpriteHeight());
	}
	else
	{
		width = int(transform->scale.x * 88);
		height = int(transform->scale.y * 88);
	}
}
