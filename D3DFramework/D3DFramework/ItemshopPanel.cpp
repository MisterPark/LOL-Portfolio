#include "stdafx.h"
#include "ItemshopPanel.h"
// Control
#include "Button.h"
#include "Label.h"
#include "OutlinedSlot.h"
#include <sstream>

ItemshopPanel* pItemshopPanel = nullptr;

ItemshopPanel::ItemshopPanel()
{
    int screenW = MainGame::GetWidth();
    int screenH = MainGame::GetHeight();
	
    auto backgroundTex = RenderManager::GetTexture(L"itemshop_background");
    SetLocation(screenW * 0.5f - backgroundTex->GetSpriteWidth() * 0.5f, screenH * 0.5f - backgroundTex->GetSpriteHeight() * 0.5f);

    AddChild<UI>(L"background", new UI(L"itemshop_background", Vector2(0, 0)));

    auto title_label = AddChild<Label>(L"titleLabel", new Label());
    title_label->transform->position = { 40.f, 40.f, 0 };
    title_label->align = Label::Align::Left;
    title_label->valign = Label::VAlign::Middle;
    title_label->foreColor = D3DCOLOR_ARGB(255, 177, 174, 160);
    title_label->text = L"상점";

    auto topitemtitle_label = AddChild<Label>(L"topitemtitleLabel", new Label());
    topitemtitle_label->transform->position = { 622.f, 40.f, 0 };
    topitemtitle_label->align = Label::Align::Left;
    topitemtitle_label->valign = Label::VAlign::Middle;
    topitemtitle_label->foreColor = D3DCOLOR_ARGB(255, 177, 174, 160);
    topitemtitle_label->text = L"상위 아이템";

    auto currentgold_label = AddChild<Label>(L"currentgoldLabel", new Label(15));
    currentgold_label->transform->position = { 260.f, 677.f, 0 };
    currentgold_label->align = Label::Align::Left;
    currentgold_label->valign = Label::VAlign::Middle;
    currentgold_label->foreColor = D3DCOLOR_ARGB(255, 191, 179, 138);
    currentgold_label->text = L"0";

    auto btn_sel = AddChild<Button>(L"selectbtn", new Button(L"itemshop_button_sel_default", Vector2(22,  662)));
    auto btn_sel_label = dynamic_cast<Label*>(btn_sel->AddChild<Label>(L"selLabel", new Label(15)));
    auto btnSelTex = RenderManager::GetTexture(L"itemshop_button_sel_default");
    btn_sel_label->transform->position = { btnSelTex->GetSpriteWidth() * 0.5f, btnSelTex->GetSpriteHeight() * 0.5f, 0 };
    btn_sel_label->align  = Label::Align::Center;
    btn_sel_label->valign = Label::VAlign::Middle;
    btn_sel_label->foreColor = D3DCOLOR_ARGB(255, 177, 174, 160);
    btn_sel_label->text = L"판매";

    auto btn_res = AddChild<Button>(L"restorebtn", new Button(L"itemshop_button_restore_default", Vector2(134, 662)));
    auto btn_res_label = dynamic_cast<Label*>(btn_res->AddChild<Label>(L"restoreLabel", new Label(15)));
    auto btnResTex = RenderManager::GetTexture(L"itemshop_button_restore_default");
    btn_res_label->transform->position = { btnResTex->GetSpriteWidth() * 0.5f, btnResTex->GetSpriteHeight() * 0.5f, 0 };
    btn_res_label->align  = Label::Align::Center;
    btn_res_label->valign = Label::VAlign::Middle;
    btn_res_label->foreColor = D3DCOLOR_ARGB(255, 177, 174, 160);
    btn_res_label->text = L"되돌리기";

    auto btn_buy = AddChild<Button>(L"buybtn", new Button(L"itemshop_button_buy_default", Vector2(619, 659)));
    btn_buy->transform->scale = { 0.9136f, 0.9136f, 0.f };
    auto btn_buy_label = dynamic_cast<Label*>(btn_buy->AddChild<Label>(L"buyLabel", new Label(15)));
    auto btnBuyTex = RenderManager::GetTexture(L"itemshop_button_buy_default");
    btn_buy_label->transform->position = { btnBuyTex->GetSpriteWidth() * 0.5f, btnBuyTex->GetSpriteHeight() * 0.5f, 0 };
    btn_buy_label->align = Label::Align::Center;
    btn_buy_label->valign = Label::VAlign::Middle;
    btn_buy_label->foreColor = D3DCOLOR_ARGB(255, 177, 174, 160);
    btn_buy_label->text = L"구매";

    auto btn_close = AddChild<Button>(L"close", new Button(L"itemshop_button_close_default", Vector2(958, 23)));
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
            std::wstringstream ws;
            ws << L"leftslot" << index;
            
            slot[index] = (OutlinedSlot*)AddChild<OutlinedSlot>(ws.str(), new OutlinedSlot(L"itemshop_item_outline", Vector2(startx + (x * intervalx), starty + (y * intervaly))));
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

void ItemshopPanel::Update()
{
    GameObject::Update();

    if (InputManager::GetKeyDown('P'))
    {
        isVisible = !isVisible;
        isVisible ? Show() : Hide();
    }
}
