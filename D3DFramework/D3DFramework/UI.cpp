#include "stdafx.h"
#include "UI.h"
#include "UIRenderer.h"

list<UI*> uiList;

UI::UI()
{
	mesh = (Rectangle*)AddComponent<PKH::Rectangle>(L"Mesh");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);

	KST::UIRenderer* renderer = new KST::UIRenderer(this);
	renderer->SetMesh(mesh);
	AddComponent(L"renderer", renderer);
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

void UI::UpdateEvent()
{
	float dt = TimeManager::DeltaTime();
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
			if(clickFlag)
			{
				clickFlag = false;
				OnDoubleClick();
			}
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
				clickFlag = true;
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

	if (clickFlag)
	{
		doubleClickTick += dt;
		if (doubleClickTick >= doubleClickDelay)
		{
			clickFlag = false;
		}
	}
	else
	{
		doubleClickTick = 0.f;
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

void PKH::UI::OnDoubleClick()
{
	if (DoubleClick != nullptr)
	{
		DoubleClick();
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
	transform->scale.x = w;
	transform->scale.y = h;
	width = w;
	height = h;
}

void PKH::UI::SetSizeByTexture()
{
	if (texture == nullptr)return;
	SetSize(texture->GetSpriteWidth(), texture->GetSpriteHeight());
}

void PKH::UI::SetLocation(int x, int y)
{
	transform->position.x = (float)x;
	transform->position.y = (float)y;
}

void PKH::UI::SetLocation(float x, float y)
{
	transform->position.x = x;
	transform->position.y = y;
}

void PKH::UI::SetLocation(Vector2 pos)
{
	transform->position.x = pos.x;
	transform->position.y = pos.y;
}

void UI::SetTexture(const wstring& _key)
{
	texture = RenderManager::GetTexture(_key);
	SetSize(texture->GetSpriteWidth(), texture->GetSpriteHeight());
	mesh->SetTexture(_key);
}

