#include "stdafx.h"
#include "UI.h"
#include "UIRenderer.h"
#include "Label.h"

bool UI::isPointerOverUI = false;
list<UI*> uiList;

UI::UI()
{
	uiList.push_back(this);

	oldEnable = enable;

	mesh = (Rectangle*)AddComponent<Engine::Rectangle>(L"Mesh");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);

	Engine::UIRenderer* renderer = new Engine::UIRenderer(this);
	renderer->SetMesh(mesh);
	AddComponent(L"renderer", renderer);

}

Engine::UI::UI(const Vector2& pos)
	: UI()
{
	SetLocation(pos);
}

Engine::UI::UI(const std::wstring& _tag, const Vector2& pos)
	: UI()
{
	SetTexture(_tag);
	SetLocation(pos);
}

UI::~UI()
{
	uiList.remove(this);

	mesh = nullptr;
	texture = nullptr;
}

void Engine::UI::Initialize()
{
}

void Engine::UI::Release()
{
}

void Engine::UI::PreUpdate()
{
	GameObject::PreUpdate();
	UpdateEvent();
}

void Engine::UI::Update()
{
	GameObject::Update();
}


void UI::UpdateEvent()
{
	// EnabledChanged
	if (enable != oldEnable)
	{
		oldEnable = enable;
		OnEnabledChanged();
	}

	// TextChanged
	if (text != oldText)
	{
		oldText = text;
		OnTextChanged();
	}

	if (visible == false) return;
	if (enable == false) return;

	float dt = Time::DeltaTime();
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
		isPointerOverUI = true;
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

	if (Input::GetMouseLButtonDown())
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
	if (Input::GetMouseLButtonUp())
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
	if (Input::GetMouseRButtonDown())
	{
		if (isHover)
		{
			isRButtonDown = true;
			OnRButtonDown();
		}
	}
	if (Input::GetMouseRButtonUp())
	{
		if (isHover)
		{
			OnRButtonUp();
			if (isRButtonDown)
			{
				OnRClick();
			}
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
	MouseEventArg args{};
	Hover.Invoke(this, args);
}

void UI::OnLeave()
{
	MouseEventArg args{};
	Leave.Invoke(this, args);
}

void UI::OnLButtonDown()
{
	MouseEventArg args{};
	LButtonDown.Invoke(this, args);
}

void UI::OnLButtonUp()
{
	MouseEventArg args{};
	LButtonUp.Invoke(this, args);
}

void UI::OnRButtonDown()
{
	MouseEventArg args{};
	RButtonDown.Invoke(this, args);
}

void UI::OnRButtonUp()
{
	MouseEventArg args{};
	RButtonUp.Invoke(this, args);
}

void UI::OnClick()
{
	MouseEventArg args{};
	Click.Invoke(this, args);
}

void Engine::UI::OnRClick()
{
}

void Engine::UI::OnDoubleClick()
{
	MouseEventArg args{};
	DoubleClick.Invoke(this, args);
}

void Engine::UI::OnEnabledChanged()
{
	MouseEventArg args{};
	EnabledChanged.Invoke(this, args);
}

void Engine::UI::OnTextChanged()
{
	MouseEventArg args{};
	TextChanged.Invoke(this, args);
}

Vector2 Engine::UI::GetSize()
{
	Matrix world = transform->GetWorldMatrix();
	Vector2 size = this->size;
	size.x *= world._11;
	size.y *= world._22;
	return size;
}

Vector2 Engine::UI::GetLocation()
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

void Engine::UI::SetSizeByTexture()
{
	if (texture == nullptr)return;
	SetSize(texture->GetSpriteWidth(), texture->GetSpriteHeight());
}

void Engine::UI::SetLocation(int x, int y)
{
	transform->position.x = (float)x;
	transform->position.y = (float)y;
}

void Engine::UI::SetLocation(float x, float y)
{
	transform->position.x = x;
	transform->position.y = y;
}

void Engine::UI::SetLocation(Vector2 pos)
{
	transform->position.x = pos.x;
	transform->position.y = pos.y;
}

void UI::SetTexture(const wstring& _key)
{
	
	texture = RenderManager::GetTexture(_key);
	mesh->SetTexture(_key);
	SetSizeByTexture();
}

void Engine::UI::SetText(const wstring& _text)
{
	text = _text;
}

void Engine::UI::SetText(int _value)
{
	WCHAR wstr[16] = {};
	swprintf_s(wstr, L"%d", _value);
	text = wstr;
}

void Engine::UI::SetText(LPCTSTR pszStr, ...)
{
	va_list args;
	va_start(args, pszStr);

	int len = _vsctprintf(pszStr, args) + 1; // for '\0'

	TCHAR* pBuf = (TCHAR*)malloc(sizeof(TCHAR) * len);

	if (pBuf)
	{
		_vstprintf_s(pBuf, len, pszStr, args);
		text = pBuf;
		free(pBuf);
	}

	va_end(args);
}

Engine::UI* Engine::UI::CreateChild(const std::wstring& _tag, const Vector2& _pos)
{
	UI* ui = GameObject::CreateChild<UI>(_tag);
	ui->SetTexture(_tag);
	ui->SetLocation(_pos);

	return ui;

	/*UI* ui = new UI(_tag, _pos);
	if (ui == nullptr) return nullptr;

	children.emplace(_tag, ui);
	ui->SetParent(this);
	return ui;*/
}

bool Engine::UI::Intersect(Vector2 _target)
{
	RECT rc = GetRect();
	if (_target.x < rc.left) return false;
	if (_target.x > rc.right) return false;
	if (_target.y < rc.top) return false;
	if (_target.y > rc.bottom) return false;
	return true;
}

RECT Engine::UI::GetRect()
{
	RECT rc;
	Matrix world = transform->GetWorldMatrix();
	rc.left = (LONG)world._41;
	rc.top = (LONG)world._42;
	rc.right = (LONG)(world._41 + (size.x * world._11));
	rc.bottom = (LONG)(world._42 + (size.y * world._22));
	return rc;
}

Texture* Engine::UI::GetTexture()
{
	return texture;
}

void Engine::UI::BringToTop()
{
	UIRenderer* renderer = (UIRenderer*)GetComponent<UIRenderer>();
	renderer->BringToTop();
}

void Engine::UI::SetPointerOverUI(bool _isOver)
{
	isPointerOverUI = _isOver;
}

bool Engine::UI::IsPointerOverUI()
{
	return isPointerOverUI;
}

void Engine::UI::HideAllUI()
{
	for (auto& ui : uiList)
	{
		if (dynamic_cast<Cursor*>(ui)) continue;
		ui->Hide();
	}
}

