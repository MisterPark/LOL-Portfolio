#include "stdafx.h"
#include "OutlinedSlot.h"
#include "Rectangle.h"

OutlinedSlot::OutlinedSlot(const std::wstring& _tagOutline, const Vector2& pos, bool backicon)
	: UI(pos)
{
	if (backicon) {
		icon = AddChild<UI>(L"icon", new UI(Vector2(0, 0)));
		outline = CreateChild(_tagOutline, Vector2(0, 0));
	}
	else {
		outline = CreateChild(_tagOutline, Vector2(0, 0));
		icon = AddChild<UI>(L"icon", new UI(Vector2(0, 0)));
	}
	renderer = icon->GetComponent<UIRenderer>();
	
	Initialize();
}

OutlinedSlot::~OutlinedSlot()
{
	Release();
}

void OutlinedSlot::Initialize()
{
}

void OutlinedSlot::Release()
{
}

void OutlinedSlot::Update()
{
	UI::Update();
	cooltime -= Time::DeltaTime();
	renderer->SetTimerRatio(1.f - cooltime / 60.f);
}

void OutlinedSlot::SetIcon(const std::wstring& _tag)
{
	icon->SetTexture(_tag);

	Vector2 outlineSize = outline->GetSize();
	Vector2 iconSize = icon->GetSize();
	icon->SetLocation((outlineSize.x - iconSize.x) * 0.5f, (outlineSize.y - iconSize.y) * 0.5f);
}

void OutlinedSlot::SetCooltime(float _cooltime)
{
	cooltime = _cooltime;
}
