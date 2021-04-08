#include "stdafx.h"
#include "Slot.h"
#include "Item.h"

Slot::Slot()
{
}

Slot::~Slot()
{
}

bool Slot::Push(UINT _id)
{
    Item* _item = ItemManager::GetInstance()->GetItem(_id);
    if (_item == nullptr) return false;

    switch (_item->GetType())
    {
    case ItemType::Consume:
        if (item->GetId() != _id) return false;
        if (num >= 5) return false;
        
        num++;

        break;

    default:
        if (item != nullptr) return false;

        item = _item->Clone();

        break;
    }
    
    return true;
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
    delete item;
    item = nullptr;
    num = 0;
}
