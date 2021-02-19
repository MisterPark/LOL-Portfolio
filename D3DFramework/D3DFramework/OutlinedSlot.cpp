#include "stdafx.h"
#include "OutlinedSlot.h"
#include "Rectangle.h"

OutlinedSlot::OutlinedSlot(const std::wstring& _tagOutline, const Vector2& pos)
	: UI(pos)
{
	outline = CreateChild(_tagOutline, Vector2(0, 0));
	icon = AddChild<UI>(L"icon", new UI(Vector2(0, 0)));

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
}

void OutlinedSlot::AddIcon(const std::wstring& _tag)
{
	icon->SetTexture(_tag);

	Vector2 outlineSize = outline->GetSize();
	Vector2 iconSize = icon->GetSize();
	icon->SetLocation((outlineSize.x - iconSize.x) * 0.5f, (outlineSize.y - iconSize.y) * 0.5f);
}
