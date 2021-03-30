#include "stdafx.h"
#include "ItemshopSlot.h"
#include "ItemManager.h"
#include "ItemshopPanel.h"
// Control
#include "Button.h"
#include "Label.h"
#include "OutlinedSlot.h"

ItemshopSlot::ItemshopSlot(Vector2 _pos, Item* _item)
    : Button(L"itemshop_blankslot", _pos)
{
    item = _item;

    //button = AddChild<Button>(L"button", new Button(L"itemshop_blankslot", Vector2(-6, -6)));
    SetTextureHover(L"itemshop_hoveritem");
    SetTexturePressed(L"itemshop_hoveritem");
    
    selectUI = AddChild<UI>(L"select", new UI(L"itemshop_selecteditem", Vector2(0, 0)));

    slot = AddChild<OutlinedSlot>(L"slot", new OutlinedSlot(L"itemshop_item_outline", Vector2(6, 6), false));
    slot->icon->transform->scale = { 0.56f, 0.56f, 0.f };

    price = AddChild<Label>(L"price", new Label(16));
    price->SetLocation(Vector2(27, 55));
    price->align = Label::Align::Center;
    price->valign = Label::VAlign::Middle;
    price->foreColor = D3DCOLOR_ARGB(255, 196, 182, 139);


    if (item != nullptr) {
        slot->SetIcon(item->icon);
        price->SetText(L"%d", item->price);
    }
}

ItemshopSlot::~ItemshopSlot()
{
}

void ItemshopSlot::Update()
{
    GameObject::Update();

    if (!visible) return;

    if (selected) {
        selectUI->Show();
    }
    else {
        selectUI->Hide();
    }
}

void ItemshopSlot::OnClick()
{
    UI::OnClick();

    selected = true;
    //ItemshopPanel::GetInstance()->SetSelectItem(item->id);
}

void ItemshopSlot::OnRClick()
{
    ItemshopPanel::GetInstance()->BuyItem(item);
}

void ItemshopSlot::Show()
{
    GameObject::Show();
    if (!selected) selectUI->Hide();
}

void ItemshopSlot::Hide()
{
    GameObject::Hide();
    selected = false;
}

void ItemshopSlot::Show(bool _visible)
{
    _visible ? Show() : Hide();
}

Item* ItemshopSlot::GetItem()
{
    return item;
}

UINT ItemshopSlot::GetItemId()
{
    return item->id;
}

void ItemshopSlot::SetItem(Item* _item)
{
    item = _item;
    if (item != nullptr) {
        slot->SetIcon(item->icon);
        price->SetText(L"%d", item->price);
    }
}
