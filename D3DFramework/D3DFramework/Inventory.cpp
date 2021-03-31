#include "stdafx.h"
#include "Inventory.h"
#include "Item.h"

Inventory::Inventory()
{
    
}

Inventory::~Inventory()
{
}

bool Inventory::Push(Item* item)
{
    if (item == nullptr) return false;

    if (item->type == ItemType::Trinkets) {

    }
    else {
        for (int i = 0; i < INVENTORY_MAX - 1; ++i)
        {
            if (slots[i].item != nullptr) continue;
            slots[i].item = item;
            return true;
        }
    }

    return false;
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
