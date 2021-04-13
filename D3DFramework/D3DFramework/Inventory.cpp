#include "stdafx.h"
#include "Inventory.h"
#include "Item.h"

Inventory::Inventory()
{
    
}

Inventory::~Inventory()
{
}

void Inventory::DeleteAll()
{
    for (int i = 0; i < INVENTORY_MAX; ++i)
    {
        slots[i].Delete();
    }
}

Item* Inventory::Push(int _id)
{
    Item* item = ItemManager::GetInstance()->GetItem(_id);
    if (item == nullptr) return nullptr;

    if (item->GetType() == ItemType::Trinkets) {
        return slots[6].Push(_id);
    }
    else {
        for (int i = 0; i < INVENTORY_MAX - 1; ++i)
        {
            if (slots[i].item != nullptr) continue;
            return slots[i].Push(_id);
        }
    }

    return nullptr;
}

bool Inventory::Pop(int _idx)
{
    if ((_idx < 0) || (_idx >= INVENTORY_MAX)) return false;

    if (slots[_idx].item == nullptr) return false;

    return slots[_idx].Pop();
}

Item* Inventory::GetItem(int _idx)
{
    return slots[_idx].item;
}

int Inventory::SellItem(int _idx)
{
    if ((_idx < 0) || (_idx >= INVENTORY_MAX)) return -1;

    if (slots[_idx].item == nullptr) return -1;

    int price = slots[_idx].item->GetPrice();
    slots[_idx].Pop();

    return price;
}
