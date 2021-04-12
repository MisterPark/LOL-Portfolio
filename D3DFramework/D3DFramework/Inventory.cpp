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

bool Inventory::Push(int _id)
{
    Item* item = ItemManager::GetInstance()->GetItem(_id);
    if (item == nullptr) return false;

    if (item->GetType() == ItemType::Trinkets) {

    }
    else {
        for (int i = 0; i < INVENTORY_MAX - 1; ++i)
        {
            if (slots[i].item != nullptr) continue;
            return slots[i].Push(_id);
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

void Inventory::ItemSell(int _idx)
{
    if ((_idx < 0) || (_idx >= INVENTORY_MAX)) return;

    if (slots[_idx].item == nullptr) return;

    /*host->stat->IncreaseBaseValue(StatType::Gold, */slots[_idx].item->Sell()/*)*/;
    slots[_idx].Pop();

    return;
}
