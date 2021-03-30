#include "stdafx.h"
#include "ItemshopTreePanel.h"
#include "ItemshopSlot.h"
#include "ItemManager.h"
#include "ItemshopPanel.h"

// Control
#include "Button.h"
#include "Label.h"
#include "OutlinedSlot.h"

ItemshopTreePanel::ItemshopTreePanel()
{
}

ItemshopTreePanel::ItemshopTreePanel(Vector2 _pos)
{
    SetLocation(_pos);

    // Root Only
    rootSlot = AddChild<ItemshopSlot>(L"root", new ItemshopSlot(Vector2(163, 119), nullptr));
}

ItemshopTreePanel::~ItemshopTreePanel()
{
}

void ItemshopTreePanel::Update()
{
    GameObject::Update();

    if (!visible) return;
}

void ItemshopTreePanel::Show()
{
    GameObject::Show();

    rootSlot->selected = true;

    if (Rootitem == nullptr) rootSlot->Hide();
}

void ItemshopTreePanel::Hide()
{
    GameObject::Hide();
}

void ItemshopTreePanel::Show(bool _visible)
{
    _visible ? Show() : Hide();
}

void ItemshopTreePanel::SetRootItem(Item* _item)
{
    Rootitem = _item;
    rootSlot->SetItem(_item);
    rootSlot->Show();
    rootSlot->selected = true;
}
