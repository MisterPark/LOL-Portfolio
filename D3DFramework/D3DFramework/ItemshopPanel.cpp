#include "stdafx.h"
#include "ItemshopPanel.h"
#include "ItemManager.h"
#include "PlayerController.h"
#include "Champion.h"
#include "PlayerInfoPanel.h"
// Control
#include "Button.h"
#include "Label.h"
#include "OutlinedSlot.h"
#include "ItemshopSlot.h"
#include "ItemshopTreePanel.h"

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
    title_label->SetColor(255, 177, 174, 160);
    title_label->SetText(L"상점");

    auto topitemtitle_label = AddChild<Label>(L"topitemtitleLabel", new Label());
    topitemtitle_label->transform->position = { 622.f, 40.f, 0 };
    topitemtitle_label->align = Label::Align::Left;
    topitemtitle_label->valign = Label::VAlign::Middle;
    topitemtitle_label->SetColor(255, 177, 174, 160);
    topitemtitle_label->SetText(L"상위 아이템");

    currentGoldLabel = AddChild<Label>(L"currentgoldLabel", new Label(15));
    currentGoldLabel->transform->position = { 283.f, 677.f, 0 };
    currentGoldLabel->align = Label::Align::Left;
    currentGoldLabel->valign = Label::VAlign::Middle;
    currentGoldLabel->SetColor(255, 191, 179, 138);
    currentGoldLabel->SetText(L"0");

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
    btn_sel->Click += Engine::Handler(this, &ItemshopPanel::SellItem);
    sellButton = btn_sel;
    
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
    btn_buy->Click += Engine::Handler(this, &ItemshopPanel::BuyItem);

    auto btn_close = AddChild<Button>(L"close", new Button(L"itemshop_button_close_default", Vector2(958, 23)));
    btn_close->transform->scale = { 0.625f, 0.625f, 0.f };
    btn_close->SetTextureHover(L"itemshop_button_close_hover");
    btn_close->SetTexturePressed(L"itemshop_button_close_pressed");
    btn_close->Click += Engine::Handler(this, &ItemshopPanel::HideItemShopPanel);

    // item list
    auto itemlist = ItemManager::GetInstance()->GetItemList();
    slots.reserve(itemlist.size());

    const int startX = 41;
    const int startY = 100;
    const int intervalX = 54;
    const int intervalY = 75;
    const int itemslotX = 10;
    int idx = 0;
    int idxX = 0;
    int idxY = 0;
    for (auto item : itemlist)
    {
        idxX = idx % itemslotX;
        idxY = idx / itemslotX;

        auto slot = AddChild<ItemshopSlot>(L"leftslot", new ItemshopSlot(Vector2(startX + (idxX * intervalX), startY + (idxY * intervalY)), item.second));
        slots.push_back(slot);
        slot->Click += Engine::Handler(this, &ItemshopPanel::SelectItemList);
        idx++;
    }

    // ItemshopTree
    treePanel = AddChild<ItemshopTreePanel>(L"rightslot", new ItemshopTreePanel(Vector2(605, 106)));

    selectItemIcon = AddChild<UI>(L"selectItemIcon", new UI(L"", Vector2(619, 434)));
    selectItemIcon->transform->scale = { 0.56f, 0.56f, 0.f };

    selectItemNameLabel = AddChild<Label>(L"selectItemNameLabel", new Label(15));
    selectItemNameLabel->SetLocation(Vector2(666, 442));
    selectItemNameLabel->SetColor(255, 255, 255, 255);
    selectItemNameLabel->align = Label::Align::Left;
    selectItemNameLabel->valign = Label::VAlign::Middle;

    selectItemPriceLabel = AddChild<Label>(L"selectItemPriceLabel", new Label(15));
    selectItemPriceLabel->SetLocation(Vector2(695, 463));
    selectItemPriceLabel->SetColor(255, 191, 179, 138);
    selectItemPriceLabel->align = Label::Align::Left;
    selectItemPriceLabel->valign = Label::VAlign::Middle;

    selectItemDescLabel = AddChild<Label>(L"selectItemDescLabel", new Label(15));
    selectItemDescLabel->SetLocation(Vector2(620, 498));
    selectItemDescLabel->SetColor(255, 191, 179, 138);
    selectItemDescLabel->align = Label::Align::Left;
    selectItemDescLabel->valign = Label::VAlign::Top;
    selectItemDescLabel->SetWidthLimit(378 - (12 * 2));

    //Hide();
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
        if (!visible) Show();
        else          Hide();
    }

    if (champion != nullptr) {
        currentGoldLabel->SetText((int)champion->stat->GetBaseValue(StatType::Gold));
        if (selectedSlot == nullptr) {

        }
        else {
            Item* item = selectedSlot->GetItem();
            selectItemIcon->SetTexture(item->GetIcon());
            selectItemNameLabel->SetText(item->GetName());
            selectItemPriceLabel->SetText(item->GetPrice());
            selectItemDescLabel->SetText(item->GetDesc());
        }
    }

    if (PlayerInfoPanel::GetInstance()->GetSelectedItemIdx() == -1) {
        sellButton->enable = false;
    }
    else {
        sellButton->enable = true;
    }
}

void ItemshopPanel::Show()
{
    GameObject::Show();

    if (selectedSlot != nullptr)
        selectedSlot->selected = true;
}

void ItemshopPanel::Hide()
{
    GameObject::Hide();

    PlayerInfoPanel::GetInstance()->UnselectInventorySlot();
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

void ItemshopPanel::SetTarget(Champion* _target)
{
    champion = _target;
    if (_target == nullptr) return;
}

void ItemshopPanel::HideItemShopPanel(GameObject* sender, MouseEventArg* args)
{
    this->Hide();
}

void ItemshopPanel::BuyItem(Item* item)
{
    if (item == nullptr) return;
    if (champion == nullptr) return;

    champion->BuyItem(item);
}

void ItemshopPanel::BuyItem(GameObject* sender, MouseEventArg* args)
{
    if (selectedSlot == nullptr) return;
    if (champion == nullptr) return;

    champion->BuyItem(selectedSlot->GetItem());
}

void ItemshopPanel::SellItem(GameObject* sender, MouseEventArg* args)
{
    PlayerInfoPanel::GetInstance()->SellSelectedItem();
}

void ItemshopPanel::SetSelectItem(ItemshopSlot* _slot)
{
    // 현재 선택중으로 되어있는 아이템이 있으면 selected 취소
    if (selectedSlot != nullptr) {
        selectedSlot->selected = false;
    }
    
    selectedSlot = _slot;

    treePanel->SetRootItem(selectedSlot->GetItem());
}

void ItemshopPanel::SelectItemList(GameObject* sender, MouseEventArg* args)
{
    auto slot = dynamic_cast<ItemshopSlot*>(sender);
    if (slot == nullptr) return;

    SetSelectItem(slot);
}
