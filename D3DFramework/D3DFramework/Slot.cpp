#include "stdafx.h"
#include "Slot.h"
#include "Item.h"

Slot::Slot()
{
//	textureKey = TextureKey::UI_SLOT;
}

Slot::~Slot()
{
}

Item* Slot::GetItem()
{
    return item;
}

Item* Slot::SetItem(Item* inItem)
{
    Item* old = item;

    item = inItem;

    return old;
}

void Slot::Update()
{
	UI::Update();
}


void Slot::OnHover()
{
	UI::OnHover();

	
}

void Slot::OnLeave()
{
	UI::OnLeave();

}

void Slot::OnClick()
{
	UI::OnClick();

	
}

void Slot::OnRButtonDown()
{
	UI::OnRButtonDown();

	Use();
}

void Slot::Use()
{
#if 0
	if (item != nullptr)
	{
		item->Use();
		if (item->count < 1)
		{
			delete item;
			item = nullptr;

		}
	}
#endif
}

void Slot::Initialize()
{
}

void Slot::Release()
{
}