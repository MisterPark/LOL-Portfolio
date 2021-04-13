#include "stdafx.h"
#include "Slot.h"
#include "Item.h"

Slot::Slot()
{
}

Slot::~Slot()
{
}

Item* Slot::Push(UINT _id)
{
    Item* _item = ItemManager::GetInstance()->GetItem(_id);
    if (_item == nullptr) return nullptr;

    switch (_item->GetType())
    {
    case ItemType::Consume:
        if (item->GetId() != _id) return nullptr;
        if (num >= 5) return nullptr;
        
        num++;
        return item;

        break;

    case ItemType::Trinkets:

        break;

    default:
        if (item != nullptr) return nullptr;

        item = _item->Clone();

        return item;
        break;
    }
    
    return nullptr;
}

bool Slot::Pop()
{
    if (item == nullptr) return false;

    switch (item->GetType())
    {
    case ItemType::Consume:
        if ((--num) <= 0) {
            Delete();
        }
        break;

    default:
        Delete();

        break;
    }


    return true;
}

void Slot::Delete()
{
    if (item != nullptr) {
        delete item;
        item = nullptr;
    }
    num = 0;
}
