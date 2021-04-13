#include "stdafx.h"
#include "Form.h"
#include "Rectangle.h"

Form::Form(const Vector2& size, const Vector2& pos)
{
	SetLocation(pos);

	std::wstring textag[(UINT)pos::end] = {
		L"tooltipatlas_lt",
		L"tooltipatlas_t",
		L"tooltipatlas_rt",
		L"tooltipatlas_l",
		L"tooltipatlas_c",
		L"tooltipatlas_r",
		L"tooltipatlas_lb",
		L"tooltipatlas_b",
		L"tooltipatlas_rb"
	};
	
	ui[(UINT)pos::lt] = AddChild<UI>(L"FormLT", new UI(textag[(UINT)pos::lt], Vector2(0.f, 0.f)));
	ui[(UINT)pos::t]  = AddChild<UI>(L"FormT",  new UI(textag[(UINT)pos::t],  Vector2(0.f, 0.f)));
	ui[(UINT)pos::rt] = AddChild<UI>(L"FormRT", new UI(textag[(UINT)pos::rt], Vector2(0.f, 0.f)));
	ui[(UINT)pos::l]  = AddChild<UI>(L"FormL",  new UI(textag[(UINT)pos::l],  Vector2(0.f, 0.f)));
	ui[(UINT)pos::c]  = AddChild<UI>(L"FormC",  new UI(textag[(UINT)pos::c],  Vector2(0.f, 0.f)));
	ui[(UINT)pos::r]  = AddChild<UI>(L"FormR",  new UI(textag[(UINT)pos::r],  Vector2(0.f, 0.f)));
	ui[(UINT)pos::lb] = AddChild<UI>(L"FormLB", new UI(textag[(UINT)pos::lb], Vector2(0.f, 0.f)));
	ui[(UINT)pos::b]  = AddChild<UI>(L"FormB",  new UI(textag[(UINT)pos::b],  Vector2(0.f, 0.f)));
	ui[(UINT)pos::rb] = AddChild<UI>(L"FormRB", new UI(textag[(UINT)pos::rb], Vector2(0.f, 0.f)));

	SetSize(size);
}

Form::~Form()
{
	Release();
}

void Form::Initialize()
{
}

void Form::Release()
{
}

void Form::Update()
{
	UI::Update();
}

Vector2 Form::GetSize()
{
	return size;
}

void Form::SetSize(const Vector2& _size)
{
	std::wstring textag[(UINT)pos::end] = {
		L"tooltipatlas_lt",
		L"tooltipatlas_t",
		L"tooltipatlas_rt",
		L"tooltipatlas_l",
		L"tooltipatlas_c",
		L"tooltipatlas_r",
		L"tooltipatlas_lb",
		L"tooltipatlas_b",
		L"tooltipatlas_rb"
	};

	Texture* tex[(UINT)pos::end] = { nullptr, };
	for (int i = 0; i < (UINT)pos::end; ++i) {
		tex[i] = RenderManager::GetTexture(textag[i]);
	}

	float ws = _size.x / tex[(UINT)pos::c]->GetSpriteWidth(); // width scale
	float hs = _size.y / tex[(UINT)pos::c]->GetSpriteHeight(); // height scale
	
	ui[(UINT)pos::lt]->SetLocation(Vector2(0.f,                                            0.f));
	ui[(UINT)pos::t]->SetLocation( Vector2((float)ui[(UINT)pos::lt]->GetSize().x,          0.f));
	ui[(UINT)pos::rt]->SetLocation(Vector2((float)ui[(UINT)pos::lt]->GetSize().x + _size.x, 0.f));
	ui[(UINT)pos::l]->SetLocation( Vector2(0.f,                                            (float)ui[(UINT)pos::lt]->GetSize().y));
	ui[(UINT)pos::c]->SetLocation( Vector2((float)ui[(UINT)pos::lt]->GetSize().x,          (float)ui[(UINT)pos::lt]->GetSize().y));
	ui[(UINT)pos::r]->SetLocation( Vector2((float)ui[(UINT)pos::lt]->GetSize().x + _size.x, (float)ui[(UINT)pos::rt]->GetSize().y));
	ui[(UINT)pos::lb]->SetLocation(Vector2(0.f,                                            (float)ui[(UINT)pos::rt]->GetSize().y + _size.y));
	ui[(UINT)pos::b]->SetLocation( Vector2((float)ui[(UINT)pos::lt]->GetSize().x,          (float)ui[(UINT)pos::rt]->GetSize().y + _size.y));
	ui[(UINT)pos::rb]->SetLocation(Vector2((float)ui[(UINT)pos::lt]->GetSize().x + _size.x, (float)ui[(UINT)pos::rt]->GetSize().y + _size.y));

	ui[(UINT)pos::t]->transform->scale = { ws,  1.f, 1.f };
	ui[(UINT)pos::b]->transform->scale = { ws,  1.f, 1.f };
	ui[(UINT)pos::l]->transform->scale = { 1.f, hs,  1.f };
	ui[(UINT)pos::r]->transform->scale = { 1.f, hs,  1.f };
	ui[(UINT)pos::c]->transform->scale = { ws,  hs,  1.f };


	//size = Vector2(_size.x + l + r, _size.y + t + b);
	size = _size;
}
