#include "stdafx.h"
#include "ItemshopTreePanel.h"
#include "ItemshopSlot.h"
#include "ItemManager.h"
#include "ItemshopPanel.h"

// Control
#include "Button.h"
#include "Label.h"
#include "OutlinedSlot.h"
#include "Tooltip.h"

ItemshopTreePanel::ItemshopTreePanel()
{
}

ItemshopTreePanel::ItemshopTreePanel(Vector2 _pos)
{
    SetLocation(_pos);

    // Root Only
    rootSlot = AddChild<ItemshopSlot>(L"root", new ItemshopSlot(Vector2(163, 119), nullptr));
    
    rootSlot->Hover += Engine::Handler(this, &ItemshopTreePanel::ShowTooltipItem);
    rootSlot->Leave += Engine::Handler(this, &ItemshopTreePanel::HideTooltipItem);
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

void ItemshopTreePanel::ShowTooltipItem(GameObject* sender, MouseEventArg* args)
{
    Tooltip* tooltip = nullptr;

    auto iter = sender->children.find(L"tooltip");
    if (sender->children.end() == iter) {
        iter = sender->children.emplace(L"tooltip", nullptr).first;
    }

    ItemshopSlot* slot = dynamic_cast<ItemshopSlot*>(sender);
    if (slot == nullptr) return;

    Item* item = slot->GetItem();
    if (item == nullptr) return;

    iter->second = tooltip = new Tooltip(item);

    Vector3 cursorPos = Cursor::GetMousePos();
    tooltip->SetLocation(Vector2(cursorPos.x, cursorPos.y));
    tooltip->Show();
}

void ItemshopTreePanel::HideTooltipItem(GameObject* sender, MouseEventArg* args)
{
    auto iter = sender->children.find(L"tooltip");
    if (sender->children.end() == iter) return;

    delete iter->second;
    iter->second = nullptr;
}
