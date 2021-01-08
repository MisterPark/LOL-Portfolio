#include "stdafx.h"
#include "UI.h"


UI::UI()
{
	mesh = (Rectangle*)AddComponent<PKH::Rectangle>(L"Mesh");
}

UI::~UI()
{
	mesh = nullptr;
	texture = nullptr;
}

void UI::Update()
{
	UpdateEvent();
	GameObject::Update();
	Billboard();
}

void UI::Render()
{
	Matrix ortho = Camera::main->GetOrthogonalMatrix();
	Matrix perspective = Camera::main->GetPerspectiveMatrix();

	RenderManager::GetDevice()->SetTransform(D3DTS_PROJECTION, &ortho);

	//RenderManager::DrawUI(textureKey, *transform, 0);
	GameObject::Render();

	if (textRenderFlag)
	{
		Vector3 pos = transform->position + textOffsetPosition;
		RenderManager::DrawFont(text, pos.x, pos.y, D3DCOLOR_XRGB(0, 0, 0));
	}

	RenderManager::GetDevice()->SetTransform(D3DTS_PROJECTION, &perspective);
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

Vector3 PKH::UI::GetSize()
{
	Vector3 size = transform->scale;
	size.x *= 2.f;
	size.y *= 2.f;
	return size;
}

Vector3 PKH::UI::GetLocation()
{
	Vector3 screenPos = Camera::main->WorldToScreenPoint(transform->position);

	return screenPos;
}

void UI::SetSize(int w, int h)
{
	transform->scale.x = w * 0.5f;
	transform->scale.y = h * 0.5f;
}

void PKH::UI::SetLocation(int x, int y)
{
	int screenW = MainGame::GetWidth();
	int screenH = MainGame::GetHeight();
	transform->position.x = x - (screenW * 0.5f) + transform->scale.x;
	transform->position.y = -y + (screenH * 0.5f) - transform->scale.y;
}

void UI::SetTexture(const wstring& _key)
{
	texture = RenderManager::GetTexture(_key);
	mesh->SetTexture(_key);
}
