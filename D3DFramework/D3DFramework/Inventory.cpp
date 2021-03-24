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
