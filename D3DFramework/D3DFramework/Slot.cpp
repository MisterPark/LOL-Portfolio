#include "stdafx.h"
#include "Slot.h"
#include "Item.h"

Slot::Slot()
{
}

Slot::~Slot()
{
}

bool Slot::Pop()
{
    if (item == nullptr) return false;

    switch (item->type)
    {
    case ItemType::Consume:
        if ((--num) <= 0) {
            item = nullptr;
            num = 0;
        }
        break;

    default:
        item = nullptr;
        num = 0;

        break;
    }


    return true;
}
