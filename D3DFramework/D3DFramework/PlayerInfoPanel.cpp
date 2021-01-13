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

    mainPanel = new HUD();
    mainPanel->SetTexture(L"panel (5)");

    
    mainPanel->SetSizeByTexture();
    mainPanel->SetLocation((screenW - mainPanelTex->GetSpriteWidth()) * 0.5f,
        100);// float(screenH - mainPanelTex->GetSpriteHeight()));

    miniPanelPos = { float(screenW - miniPanelTex->GetSpriteWidth()),
                    0.f,0.f };
    invenPanelPos = { mainPanelPos.x + mainPanelTex->GetSpriteWidth()-25,
                    float(screenH - invenPanelTex->GetSpriteHeight()),
                    0.f };
    faceBorderPos = { mainPanelPos.x - faceBorderTex->GetSpriteWidth() * 0.6f,
                     mainPanelPos.y+10 ,0.f };
}

PlayerInfoPanel::~PlayerInfoPanel()
{
    delete mainPanel;
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
    //RenderManager::DrawUI(L"panel (2)", invenPanelPos);
    //RenderManager::DrawUI(L"panel (5)", mainPanelPos);
    //RenderManager::DrawUI(L"panel (1)", faceBorderPos);
}
