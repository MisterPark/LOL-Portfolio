#include "stdafx.h"
#include "PlayerInfoPanel.h"
#include "Rectangle.h"
#include "UI.h"
#include "Champion.h"
#include "Label.h"

PlayerInfoPanel* pPlayerInfoPanel = nullptr;

PlayerInfoPanel::PlayerInfoPanel()
{
    screenW = MainGame::GetWidth();
    screenH = MainGame::GetHeight();

    mainPanelTex = RenderManager::GetTexture(L"panel (5)");
    miniPanelTex = RenderManager::GetTexture(L"panel (4)");
    faceBorderTex = RenderManager::GetTexture(L"panel (1)");
    invenPanelTex = RenderManager::GetTexture(L"panel (2)");
    statPanelTex = RenderManager::GetTexture(L"stat_panel (5)");

    Vector2 mainPanelPos{ (screenW - mainPanelTex->GetSpriteWidth()) * 0.5f, float(screenH - mainPanelTex->GetSpriteHeight())};
    Vector2 miniPanelPos{ float(screenW - miniPanelTex->GetSpriteWidth()), 0.f};
    Vector2 invenPanelPos{ mainPanelPos.x + mainPanelTex->GetSpriteWidth() - 25, float(screenH - invenPanelTex->GetSpriteHeight())};
    Vector2 faceBorderPos{ mainPanelPos.x - faceBorderTex->GetSpriteWidth() * 0.6f, mainPanelPos.y + 10};
    Vector2 statPanelPos{ faceBorderPos.x - statPanelTex->GetSpriteWidth() * 0.8f, faceBorderPos.y};

    statPanel = new UI(L"stat_panel (5)", statPanelPos);
    mainPanel = new UI(L"panel (5)", mainPanelPos);
    miniPanel = new UI(L"panel (4)", miniPanelPos);
    invenPanel = new UI(L"panel (2)", invenPanelPos);
    facePanel = new UI(L"garen_circle", Vector2(faceBorderPos.x + 20, faceBorderPos.y + 20));
    faceBorder = new UI(L"panel (1)", faceBorderPos);

    Vector2 scaleHP{ 1,1 };
    Vector2 scaleMP{ 1,1 };
    Vector2 hpOffsetPos{ 76,124 };
    Vector2 mpOffsetPos{ 76,146 };
    Vector2 barTipOffset1{ 71,124 };
    Vector2 barTipOffset2{ 535,124 };
    Vector2 barTipOffset3{ 71,146 };
    Vector2 barTipOffset4{ 535,146 };

    hpLabel = new Label();
    hpLabel->transform->position = { mainPanelPos.x + 303, mainPanelPos.y + 124,0 };
    hpLabel->align = Label::Align::Center;
    hpLabel->foreColor = D3DCOLOR_ARGB(255, 254, 254, 254);

    mpLabel = new Label();
    mpLabel->transform->position = { mainPanelPos.x + 303, mainPanelPos.y + 146,0 };
    mpLabel->align = Label::Align::Center;
    mpLabel->foreColor = D3DCOLOR_ARGB(255, 254, 254, 254);

    for (int i = 0; i < 8; i++)
    {
        statLabel[i] = new Label();
        statLabel[i]->foreColor = D3DCOLOR_ARGB(255, 254, 254, 254);
    }
    

    Vector2 spellPos{ (float)(mainPanelPos.x + 126), (float)(mainPanelPos.y + 31) };
    int spellPadding = 6;
    int spellSize = 64;

    slotSpell1 = new UI(Vector2(spellPos.x + ((spellSize + 4) + spellPadding) * 0 + 3, spellPos.y + 3));
    slotSpell2 = new UI(Vector2(spellPos.x + ((spellSize + 4) + spellPadding) * 1 + 3, spellPos.y + 3));
    slotSpell3 = new UI(Vector2(spellPos.x + ((spellSize + 4) + spellPadding) * 2 + 3, spellPos.y + 3));
    slotSpell4 = new UI(Vector2(spellPos.x + ((spellSize + 4) + spellPadding) * 3 + 3, spellPos.y + 3));
    
    int passiveSize = 50;

    slotPassive = new UI(Vector2(mainPanelPos.x + 70, mainPanelPos.y + 31));
    slotSummoner1 = new UI(Vector2(mainPanelPos.x + 434, mainPanelPos.y + 32));
    slotSummoner2 = new UI(Vector2(mainPanelPos.x + 490, mainPanelPos.y + 32));
}

PlayerInfoPanel::~PlayerInfoPanel()
{
    Safe_Delete(&statPanel);
    Safe_Delete(&mainPanel);
    Safe_Delete(&miniPanel);
    Safe_Delete(&invenPanel);
    Safe_Delete(&faceBorder);
    Safe_Delete(&facePanel);
    Safe_Delete(&hpLabel);
    Safe_Delete(&mpLabel);
    Safe_Delete(&slotSpell1);
    Safe_Delete(&slotSpell2);
    Safe_Delete(&slotSpell3);
    Safe_Delete(&slotSpell4);
    Safe_Delete(&slotPassive);
    Safe_Delete(&slotSummoner1);
    Safe_Delete(&slotSummoner2);
    for (int i = 0; i < 8; i++)
    {
        Safe_Delete(&statLabel[i]);
    }

    pPlayerInfoPanel = nullptr;
    mainPanelTex = nullptr;
    miniPanelTex = nullptr;
    faceBorderTex = nullptr;
    invenPanelTex = nullptr;
    champion = nullptr;
}

PlayerInfoPanel* PlayerInfoPanel::GetInstance()
{
    if (pPlayerInfoPanel == nullptr)
    {
        pPlayerInfoPanel = new PlayerInfoPanel();
    }
    return pPlayerInfoPanel;
}

void PlayerInfoPanel::DestroyInstance()
{
    if (pPlayerInfoPanel)
    {
        delete pPlayerInfoPanel;
        pPlayerInfoPanel = nullptr;
    }
}

void PlayerInfoPanel::Initialize()
{
}

void PlayerInfoPanel::Release()
{
}

void PlayerInfoPanel::Update()
{
    //if (InputManager::GetKeyDown(VK_UP))
    //{
    //    barTipOffset1.y -= 1;
    //    printf("offset X : %d / Y : %d\n", (int)barTipOffset1.x, (int)barTipOffset1.y);
    //}
    //if (InputManager::GetKeyDown(VK_DOWN))
    //{
    //    barTipOffset1.y += 1;
    //    printf("offset X : %d / Y : %d\n", (int)barTipOffset1.x, (int)barTipOffset1.y);
    //}
    //if (InputManager::GetKeyDown(VK_LEFT))
    //{
    //    barTipOffset1.x -= 1;
    //    printf("offset X : %d / Y : %d\n", (int)barTipOffset1.x, (int)barTipOffset1.y);
    //}
    //if (InputManager::GetKeyDown(VK_RIGHT))
    //{
    //    barTipOffset1.x += 1;
    //    printf("offset X : %d / Y : %d\n", (int)barTipOffset1.x, (int)barTipOffset1.y);
    //}

    GameObject::Update();
    mainPanel->Update();
    miniPanel->Update();
    invenPanel->Update();
    faceBorder->Update();
    facePanel->Update();
    statPanel->Update();

    hpLabel->Update();
    mpLabel->Update();

    slotSpell1->Update();
    slotSpell2->Update();
    slotSpell3->Update();
    slotSpell4->Update();
    slotPassive->Update();
    slotSummoner1->Update();
    slotSummoner2->Update();

    for (int i = 0; i < 8; i++)
    {
        statLabel[i]->Update();
    }
}
//
//void PlayerInfoPanel::Render()
//{
//    
//
//    GameObject::Render();
//    RenderStat();
//    miniPanel->Render();
//    
//    mainPanel->Render();
//    invenPanel->Render();
//    
//
//    if (champion != nullptr)
//    {
//        facePanel->Render();
//        RenderBar();
//        slotSpell1->Render();
//        slotSpell2->Render();
//        slotSpell3->Render();
//        slotSpell4->Render();
//        slotPassive->Render();
//        slotSummoner1->Render();
//        slotSummoner2->Render();
//    }
//    RenderManager::DrawUI(tipTextureKey, mainPanelPos + barTipOffset1, 0);
//    RenderManager::DrawUI(tipTextureKey, mainPanelPos + barTipOffset2, 0);
//    RenderManager::DrawUI(tipTextureKey, mainPanelPos + barTipOffset3, 0);
//    RenderManager::DrawUI(tipTextureKey, mainPanelPos + barTipOffset4, 0);
//
//    RenderManager::DrawUI(tipTextureKey, mainPanelPos + barTipOffset4, 0);
//
//    faceBorder->Render();
//}
//
//void PlayerInfoPanel::RenderStat()
//{
//    statPanel->Render();
//
//    Vector3 offset = { 15,15,0 };
//    int iconSize = 20;
//    int padding = 15;
//    Vector3 labelPos[8];
//
//    RenderManager::DrawUI(L"stat_icon (7)", statPanelPos +offset, 0);
//    labelPos[0] = statPanelPos + offset;
//    offset.y = offset.y + iconSize + padding;
//    RenderManager::DrawUI(L"stat_icon (11)", statPanelPos + offset, 0);
//    labelPos[1] = statPanelPos + offset;
//    offset.y = offset.y + iconSize + padding;
//    RenderManager::DrawUI(L"stat_icon (13)", statPanelPos + offset, 0);
//    labelPos[2] = statPanelPos + offset;
//    offset.y = offset.y + iconSize + padding;
//    RenderManager::DrawUI(L"stat_icon (1)", statPanelPos + offset, 0);
//    labelPos[3] = statPanelPos + offset;
//    offset.x = 110;
//    offset.y = 15;
//    RenderManager::DrawUI(L"stat_icon (8)", statPanelPos + offset, 0);
//    labelPos[4] = statPanelPos + offset;
//    offset.y = offset.y + iconSize + padding;
//    RenderManager::DrawUI(L"stat_icon (12)", statPanelPos + offset, 0);
//    labelPos[5] = statPanelPos + offset;
//    offset.y = offset.y + iconSize + padding;
//    RenderManager::DrawUI(L"stat_icon (16)", statPanelPos + offset, 0);
//    labelPos[6] = statPanelPos + offset;
//    offset.y = offset.y + iconSize + padding;
//    RenderManager::DrawUI(L"stat_icon (3)", statPanelPos + offset, 0);
//    labelPos[7] = statPanelPos + offset;
//
//    WCHAR wstr[32] = {};
//    if (champion != nullptr)
//    {
//        
//        _itow_s((int)champion->GetAttackDamage(), wstr, 10);
//        statLabel[0]->text = wstr;
//        _itow_s((int)champion->GetArmor(), wstr, 10);
//        statLabel[1]->text = wstr;
//        swprintf_s(wstr, L"%.02f", champion->GetAttackPerSec());
//        statLabel[2]->text = wstr;
//        _itow_s((int)champion->GetCriticalPer(), wstr, 10);
//        statLabel[3]->text = wstr;
//        _itow_s((int)champion->GetAbilityPower(), wstr, 10);
//        statLabel[4]->text = wstr;
//        _itow_s((int)champion->GetMagicResistance(), wstr, 10);
//        statLabel[5]->text = wstr;
//        _itow_s((int)champion->GetCooldownReduction(), wstr, 10);
//        statLabel[6]->text = wstr;
//        _itow_s((int)(champion->GetMovementSpeed() * 100), wstr, 10);
//        statLabel[7]->text = wstr;
//    }
//    for (int i = 0; i < 8; i++)
//    {
//        labelPos[i].x += 25;
//        statLabel[i]->transform->position = labelPos[i];
//        statLabel[i]->Render();
//    }
//}
//
//void PlayerInfoPanel::RenderMini()
//{
//}
//
//void PlayerInfoPanel::RenderBar()
//{
//    float ratioHP = 0.f;
//    float ratioMP = 0.f;
//    float maxHp = champion->GetMaxHP();
//    float maxMp = champion->GetMaxMP();
//    float hp = champion->GetHP();
//    float mp = champion->GetMP();
//    WCHAR hpText[32] = {};
//    WCHAR mpText[32] = {};
//
//    if (maxHp != 0.f)
//    {
//        ratioHP = hp / maxHp;
//        swprintf_s(hpText, L"%d / %d", (int)hp, (int)maxHp);
//        hpLabel->text = hpText;
//    }
//    if (maxMp != 0.f)
//    {
//        ratioMP = mp / maxMp;
//        swprintf_s(mpText, L"%d / %d", (int)mp, (int)maxMp);
//        mpLabel->text = mpText;
//    }
//
//    if (ratioHP < 0.f) ratioHP = 0.f;
//    if (ratioMP < 0.f) ratioMP = 0.f;
//
//    RenderManager::DrawUIHorizontal(textureKeyHP, mainPanelPos + hpOffsetPos, scaleHP, 0, ratioHP);
//    hpLabel->Render();
//    RenderManager::DrawUIHorizontal(textureKeyMP, mainPanelPos + mpOffsetPos, scaleMP, 0, ratioMP);
//    mpLabel->Render();
//}

void PlayerInfoPanel::SetTarget(Champion* _target)
{
    champion = _target;
    if (_target == nullptr) return;
    facePanel->SetTexture(champion->faceCircleTexkey);

    slotSpell1->SetTexture(champion->qTexKey);
    slotSpell2->SetTexture(champion->wTexKey);
    slotSpell3->SetTexture(champion->eTexKey);
    slotSpell4->SetTexture(champion->rTexKey);
    slotPassive->SetTexture(champion->passiveTexKey);
}
