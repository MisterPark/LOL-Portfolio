#include "stdafx.h"
#include "ItemshopPanel.h"
// Control
#include "Button.h"
#include "Label.h"
#include "OutlinedSlot.h"

ItemshopPanel* pItemshopPanel = nullptr;

ItemshopPanel::ItemshopPanel()
{
    int screenW = MainGame::GetWidth();
    int screenH = MainGame::GetHeight();
	
    auto backgroundTex = RenderManager::GetTexture(L"itemshop_background");
    SetLocation(screenW * 0.5f - backgroundTex->GetSpriteWidth() * 0.5f, screenH * 0.5f - backgroundTex->GetSpriteHeight() * 0.5f);

    AddChild(new UI(L"itemshop_background", Vector2(0, 0)));
    
    auto btn_sel = AddChild(new Button(L"itemshop_button_sel_default", Vector2(22,  662)));
    auto btn_sel_label = dynamic_cast<Label*>(btn_sel->AddChild(new Label()));
    btn_sel_label->transform->position = { 0, 0, 0 };
    btn_sel_label->align = Label::Align::Center;
    btn_sel_label->foreColor = D3DCOLOR_ARGB(255, 177, 174, 160);
    btn_sel_label->text = L"판매";

    auto btn_res = AddChild(new Button(L"itemshop_button_restore_default", Vector2(134, 662)));
    auto btn_res_label = dynamic_cast<Label*>(btn_res->AddChild(new Label()));
    btn_res_label->transform->position = { 0, 0, 0 };
    btn_res_label->align = Label::Align::Center;
    btn_res_label->foreColor = D3DCOLOR_ARGB(255, 177, 174, 160);
    btn_res_label->text = L"되돌리기";

    auto btn_buy = AddChild(new Button(L"itemshop_button_buy_default", Vector2(619, 659)));
    btn_buy->transform->scale = { 0.9136f, 0.9136f, 0.f };
    auto btn_buy_label = dynamic_cast<Label*>(btn_buy->AddChild(new Label()));
    btn_buy_label->transform->position = { 0, 0, 0 };
    btn_buy_label->align = Label::Align::Center;
    btn_buy_label->foreColor = D3DCOLOR_ARGB(255, 177, 174, 160);
    btn_buy_label->text = L"구매";

    auto btn_close = AddChild(new Button(L"itemshop_button_close_default", Vector2(958, 23)));
    btn_close->transform->scale = { 0.625f, 0.625f, 0.f };

    int startx = 57;
    int starty = 106;
    int intervalx = 51;
    int intervaly = 75;
    const int itemslotX = 10;
    const int itemslotY = 6;
    vector<OutlinedSlot*> slot;
    slot.resize(itemslotX * itemslotY);

    for (int y = 0; y < itemslotY; ++y) {
        for (int x = 0; x < itemslotX; ++x) {
            int index = x + (y * itemslotX);
            slot[index] = (OutlinedSlot*)AddChild(new OutlinedSlot(L"itemshop_item_outline", Vector2(startx + (x * intervalx), starty + (y * intervaly))));
            slot[index]->icon->transform->scale = { 0.56f, 0.56f, 0.f };
        }
    }
    // 임시
    slot[0]->AddIcon(L"1001_class_t1_bootsofspeed");

}

ItemshopPanel::~ItemshopPanel()
{
}

ItemshopPanel* ItemshopPanel::GetInstance()
{
    if (pItemshopPanel == nullptr)
    {
        pItemshopPanel = new ItemshopPanel();
    }
    return pItemshopPanel;
}

void ItemshopPanel::DestroyInstance()
{
    if (pItemshopPanel)
    {
        delete pItemshopPanel;
        pItemshopPanel = nullptr;
    }
}
