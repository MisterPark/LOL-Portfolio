#include "stdafx.h"
#include "UIManager.h"

// Loading Scene
#include "LoadingChampScreen.h"
// Game Scene
#include "PlayerInfoPanel.h"
#include "MinimapPanel.h"


UIManager* pUIManager = nullptr;

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

UIManager* UIManager::GetInstance()
{
    if (pUIManager == nullptr)
    {
        pUIManager = new UIManager();
    }
    return pUIManager;
}

void UIManager::DestroyInstance()
{
    if (pUIManager)
    {
        delete pUIManager;
        pUIManager = nullptr;
    }
}

void UIManager::AddUI(UI* _ui)
{
    ui.push_back(_ui);
    ObjectManager::GetInstance()->AddObject(_ui, Layer::UI);
}

void UIManager::DeleteListAll()
{
    ui.clear();
}
