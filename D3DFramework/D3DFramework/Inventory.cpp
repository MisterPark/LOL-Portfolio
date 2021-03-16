#include "stdafx.h"
#include "Inventory.h"
#include "Item.h"

Inventory* pInventory = nullptr;

Inventory::Inventory()
{
    position = { 700,200,0 };
    visible = false;
    
}

Inventory::~Inventory()
{
    for (int i = 0; i < dfMAX_SLOT_COUNT; i++)
    {
        Item* item = pInventory->slots[i].GetItem();
        if (item == nullptr)continue;
        delete item;

        pInventory->slots[i].SetItem(nullptr);
    }
}

Inventory* Inventory::GetInstance()
{
    if (pInventory == nullptr)
    {
        pInventory = new Inventory;
    }
    return pInventory;
}

void Inventory::Destroy()
{
    if (pInventory)
    {
        delete pInventory;
        pInventory = nullptr;
    }
}

void Inventory::Show()
{
    pInventory->visible = true;
    Cursor::Show();
}

void Inventory::Show(bool on)
{
}

void Inventory::Hide()
{
}

void Inventory::Update()
{
}

bool Inventory::Push(Item* item)
{
    return false;
}

int Inventory::GetItemCount(ItemType _type)
{
	int count = 0;
    return count;
}

void Inventory::RemoveItem(ItemType _type, int count)
{
}

void Inventory::UpdateUI()
{
}
