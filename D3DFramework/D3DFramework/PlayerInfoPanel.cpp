#include "stdafx.h"
#include "PlayerInfoPanel.h"
#include "Rectangle.h"
#include "UI.h"

PlayerInfoPanel* pPlayerInfoPanel = nullptr;

PlayerInfoPanel::PlayerInfoPanel()
{
    screenW = MainGame::GetWidth();
    screenH = MainGame::GetHeight();

    mainPanelTex = RenderManager::GetTexture(L"panel (5)");
    miniPanelTex = RenderManager::GetTexture(L"panel (4)");
    faceBorderTex = RenderManager::GetTexture(L"panel (1)");
    invenPanelTex = RenderManager::GetTexture(L"panel (2)");

    mainPanelPos = { (screenW - mainPanelTex->GetSpriteWidth()) * 0.5f,
                   float(screenH - mainPanelTex->GetSpriteHeight()),0.f };
    miniPanelPos = { float(screenW - miniPanelTex->GetSpriteWidth()),
                   0.f,0.f };
    invenPanelPos = { mainPanelPos.x + mainPanelTex->GetSpriteWidth() - 25,
                    float(screenH - invenPanelTex->GetSpriteHeight()),
                    0.f };
    faceBorderPos = { mainPanelPos.x - faceBorderTex->GetSpriteWidth() * 0.6f,
                     mainPanelPos.y + 10 ,0.f };

    mainPanel = new HUD();
    mainPanel->SetTexture(L"panel (5)");
    mainPanel->SetSizeByTexture();
    mainPanel->SetLocation(mainPanelPos.x, mainPanelPos.y);

    miniPanel = new HUD();
    miniPanel->SetTexture(L"panel (4)");
    miniPanel->SetSizeByTexture();
    miniPanel->SetLocation(miniPanelPos.x, miniPanelPos.y);

    invenPanel = new HUD();
    invenPanel->SetTexture(L"panel (2)");
    invenPanel->SetSizeByTexture();
    invenPanel->SetLocation(invenPanelPos.x, invenPanelPos.y);

    faceBorder = new HUD();
    faceBorder->SetTexture(L"panel (1)");
    faceBorder->SetSizeByTexture();
    faceBorder->SetLocation(faceBorderPos.x, faceBorderPos.y);
   
}

PlayerInfoPanel::~PlayerInfoPanel()
{
    delete mainPanel;
    delete miniPanel;
    delete invenPanel;
    delete faceBorder;
    pPlayerInfoPanel = nullptr;
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
    GameObject::Update();
    mainPanel->Update();
}

void PlayerInfoPanel::Render()
{
    GameObject::Render();
    mainPanel->Render();
    miniPanel->Render();
    invenPanel->Render();
    faceBorder->Render();
    //RenderManager::DrawUI(L"panel (2)", invenPanelPos);
    //RenderManager::DrawUI(L"panel (5)", mainPanelPos);
    //RenderManager::DrawUI(L"panel (1)", faceBorderPos);
}
