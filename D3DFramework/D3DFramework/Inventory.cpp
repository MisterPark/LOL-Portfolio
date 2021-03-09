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
    pInventory->visible = on;
    if (on)
    {
        Cursor::Show();
    }
    else
    {
        Cursor::Hide();
    }
}

void Inventory::Hide()
{
    pInventory->visible = false;
    Cursor::Hide();
}

void Inventory::Update()
{
    pInventory->UpdateUI();

    for (int i = 0; i < dfMAX_SLOT_COUNT; i++)
    {
        pInventory->slots[i].Update();
    }
}

bool Inventory::Push(Item* item)
{
    Item* out = nullptr;
    for (int i = 0; i < dfMAX_SLOT_COUNT; i++)
    {
        Item* iter = pInventory->slots[i].GetItem();
        if (iter != nullptr) // 슬롯에 아이템이 존재할 때
        {
            if (iter->type != item->type) continue;
            
            item->Destroy();
            //타입이 같으면 수량 증가
            iter->count++;
            return true;
        }

        // 슬롯에 아이템이 존재하지 않으면 셋            
        pInventory->slots[i].SetItem(item);
        SceneManager::GetCurrentScene()->RemoveObject(item);

        
        return true;
    }

    return false;
}

int Inventory::GetItemCount(ItemType _type)
{
    int count = 0;
    for (int i = 0; i < dfMAX_SLOT_COUNT; i++)
    {
        Item* item = pInventory->slots[i].GetItem();
        if (item == nullptr) continue;

        if (item->type != _type) continue;

        return item->count;
    }
    return count;
}

void Inventory::RemoveItem(ItemType _type, int count)
{
    for (int i = 0; i < dfMAX_SLOT_COUNT; i++)
    {
        Item* item = pInventory->slots[i].GetItem();
        if (item == nullptr) continue;

        if (item->type != _type) continue;

        int result = item->count -count;
        if (result < 0)
        {
            result = 0;
        }
        item->count = result;
    }
}

void Inventory::UpdateUI()
{
    Vector3 slotPosition = { position.x + 50, position.y + 100,0 };
    Vector3 slotOffset = slotPosition;

    int iter = 0;

    for (int i = 0; i < dfSLOT_ROW_COUNT; i++)
    {
        slotOffset.y = slotPosition.y + i * 40;

        for (int j = 0; j < dfSLOT_COL_COUNT; j++)
        {
            slotOffset.x = slotPosition.x + j * 40;

            slots[iter].transform->position = slotOffset;
            iter++;
        }

    }
}
