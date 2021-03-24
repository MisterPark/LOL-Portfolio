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
    currentgold_label->transform->position = { 283.f, 677.f, 0 };
    currentgold_label->align = Label::Align::Left;
    currentgold_label->valign = Label::VAlign::Middle;
    currentgold_label->foreColor = D3DCOLOR_ARGB(255, 191, 179, 138);
    currentgold_label->text = L"0";

    auto btn_sel = AddChild<Button>(L"selectbtn", new Button(L"itemshop_button_sel_default", Vector2(22,  662)));
    auto btnSelTex = RenderManager::GetTexture(L"itemshop_button_sel_default");
    btn_sel->SetText(L"판매");
    btn_sel->SetLabelSize(15);
    btn_sel->SetLabelPosition(Vector2(btnSelTex->GetSpriteWidth() * 0.5f, btnSelTex->GetSpriteHeight() * 0.5f));
    btn_sel->SetLabelAlign(Label::Align::Center);
    btn_sel->SetLabelVAlign(Label::VAlign::Middle);
    btn_sel->SetLabelColor(D3DCOLOR_ARGB(255, 177, 174, 160));
    btn_sel->SetTextureHover(L"itemshop_button_sel_hover");
    btn_sel->SetTexturePressed(L"itemshop_button_pressed");
    btn_sel->SetTextureDisable(L"itemshop_button_disabled");
    
    auto btn_res = AddChild<Button>(L"restorebtn", new Button(L"itemshop_button_restore_default", Vector2(134, 662)));
    auto btnResTex = RenderManager::GetTexture(L"itemshop_button_restore_default");
    btn_res->SetText(L"되돌리기");
    btn_res->SetLabelSize(15);
    btn_res->SetLabelPosition(Vector2(btnResTex->GetSpriteWidth() * 0.5f, btnResTex->GetSpriteHeight() * 0.5f));
    btn_res->SetLabelAlign(Label::Align::Center);
    btn_res->SetLabelVAlign(Label::VAlign::Middle);
    btn_res->SetLabelColor(D3DCOLOR_ARGB(255, 177, 174, 160));
    btn_res->SetTextureHover(L"itemshop_button_restore_hover");
    btn_res->SetTexturePressed(L"itemshop_button_pressed");
    btn_res->SetTextureDisable(L"itemshop_button_disabled");

    auto btn_buy = AddChild<Button>(L"buybtn", new Button(L"itemshop_button_buy_default", Vector2(619, 659)));
    btn_buy->transform->scale = { 0.9136f, 0.9136f, 0.f };
    auto btnBuyTex = RenderManager::GetTexture(L"itemshop_button_buy_default");
    btn_buy->SetText(L"구매");
    btn_buy->SetLabelSize(15);
    btn_buy->SetLabelPosition(Vector2(btnBuyTex->GetSpriteWidth() * 0.5f, btnBuyTex->GetSpriteHeight() * 0.5f));
    btn_buy->SetLabelAlign(Label::Align::Center);
    btn_buy->SetLabelVAlign(Label::VAlign::Middle);
    btn_buy->SetLabelColor(D3DCOLOR_ARGB(255, 177, 174, 160));
    btn_buy->SetTextureHover(L"itemshop_button_buy_hover");
    btn_buy->SetTexturePressed(L"itemshop_button_buy_pressed");
    btn_buy->SetTextureDisable(L"itemshop_button_buy_disabled");

    auto btn_close = AddChild<Button>(L"close", new Button(L"itemshop_button_close_default", Vector2(958, 23)));
    btn_close->transform->scale = { 0.625f, 0.625f, 0.f };
    btn_close->SetTextureHover(L"itemshop_button_close_hover");
    btn_close->SetTexturePressed(L"itemshop_button_close_pressed");
    btn_close->Click += Engine::Handler(this, &ItemshopPanel::ItemShop_Panel);

    int startX = 57;
    int startY = 106;
    int intervalX = 51;
    int intervalY = 75;
    const int itemslotX = 10;
    const int itemslotY = 6;
    vector<OutlinedSlot*> slot;
    slot.resize(itemslotX * itemslotY);
    vector<Button*> slotbutton;
    slot.resize(itemslotX * itemslotY);

    for (int y = 0; y < itemslotY; ++y) {
        for (int x = 0; x < itemslotX; ++x) {
            int index = x + (y * itemslotX);

            AddChild<Button>(L"leftslotbutton", new Button(L"", Vector2(startX + (x * intervalX), startY + (y * intervalY))));

            slot[index] = (OutlinedSlot*)AddChild<OutlinedSlot>(L"leftslot", new OutlinedSlot(L"itemshop_item_outline", Vector2(startX + (x * intervalX), startY + (y * intervalY)), false));
            slot[index]->icon->transform->scale = { 0.56f, 0.56f, 0.f };
        }
    }
    // 임시
    slot[0]->SetIcon(L"1001_class_t1_bootsofspeed");

    Hide();
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

    if (Input::GetKeyDown('P'))
    {
        if (!visible)    Show();
        else            Hide();
    }
}

void ItemshopPanel::ToggleVisible(GameObject* sender, MouseEventArg* arg)
{
    pItemshopPanel->visible ?
        pItemshopPanel->Hide() :
        pItemshopPanel->Show();
}

void ItemshopPanel::Close()
{
}

void ItemshopPanel::ItemShop_Panel(GameObject* sender, MouseEventArg* args)
{
    this->Hide();
}
