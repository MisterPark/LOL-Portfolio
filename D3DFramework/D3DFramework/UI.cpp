#include "stdafx.h"
#include "UI.h"
#include "UIRenderer.h"


UI::UI()
{
	mesh = (Rectangle*)AddComponent<PKH::Rectangle>(L"Mesh");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);

	KST::UIRenderer* renderer = new KST::UIRenderer(this);
	renderer->SetMesh(mesh);
	AddComponent(L"renderer", renderer);
}

PKH::UI::UI(const Vector2& pos)
	: UI()
{
	SetLocation(pos);
}

PKH::UI::UI(const std::wstring& _tag, const Vector2& pos)
	: UI()
{
	tag = _tag;
	SetTexture(_tag);
	SetSizeByTexture();
	SetLocation(pos);
}

UI::~UI()
{

	mesh = nullptr;
	texture = nullptr;
}

void PKH::UI::Initialize()
{
}

void PKH::UI::Release()
{
}

void UI::Update()
{
	UpdateEvent();
	GameObject::Update();
}

void UI::UpdateEvent()
{
	float dt = TimeManager::DeltaTime();
	Vector3 cursorPos = Cursor::GetMousePos();

	// Hover & Leave
	if (Intersect(cursorPos)) 
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
	Hover.Invoke();
}

void UI::OnLeave()
{
	Leave.Invoke();
}

void UI::OnLButtonDown()
{
	LButtonDown.Invoke();
}

void UI::OnLButtonUp()
{
	LButtonUp.Invoke();
}

void UI::OnRButtonDown()
{
	RButtonDown.Invoke();
}

void UI::OnRButtonUp()
{
	RButtonUp.Invoke();
}

void UI::OnClick()
{
	Click.Invoke();
}

void PKH::UI::OnDoubleClick()
{
	DoubleClick.Invoke();
}

Vector2 PKH::UI::GetSize()
{
	Matrix world = transform->GetWorldMatrix();
	Vector2 size = this->size;
	size.x *= world._11;
	size.y *= world._22;
	return size;
}

Vector2 PKH::UI::GetLocation()
{
	Matrix world = transform->GetWorldMatrix();
	Vector2 screenPos;
	screenPos.x = world._41;
	screenPos.y = world._42;

	return screenPos;
}

void UI::SetSize(int w, int h)
{
	size.x = (FLOAT)w;
	size.y = (FLOAT)h;
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
	//SetSize(texture->GetSpriteWidth(), texture->GetSpriteHeight());
	mesh->SetTexture(_key);
	tag = _key;
	SetSizeByTexture();
}

PKH::UI* PKH::UI::CreateChild(const std::wstring& _tag, const Vector2& _pos)
{
	UI* ui = new UI(_tag, _pos);
	if (ui == nullptr) return nullptr;

	children.emplace(_tag, ui);
	ui->SetParent(this);
	return ui;
}

bool PKH::UI::Intersect(Vector2 _target)
{
	RECT rc = GetRect();
	if (_target.x < rc.left) return false;
	if (_target.x > rc.right) return false;
	if (_target.y < rc.top) return false;
	if (_target.y > rc.bottom) return false;
	return true;
}

RECT PKH::UI::GetRect()
{
	RECT rc;
	Matrix world = transform->GetWorldMatrix();
	rc.left = (LONG)world._41;
	rc.top = (LONG)world._42;
	rc.right = (LONG)(world._41 + (size.x * world._11));
	rc.bottom = (LONG)(world._42 + (size.y * world._22));
	return rc;
}

Texture* PKH::UI::GetTexture()
{
	return texture;
}

void PKH::UI::BringToTop()
{
	UIRenderer* renderer = (UIRenderer*)GetComponent<UIRenderer>();
	renderer->BringToTop();
}

