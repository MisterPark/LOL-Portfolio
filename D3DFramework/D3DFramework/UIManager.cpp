#include "stdafx.h"
#include "UIManager.h"
#include "PlayerInfoPanel.h"

using namespace PKH;

PKH::UIManager* pUIManager = nullptr;

UIManager* PKH::UIManager::GetInstance()
{
	if (pUIManager == nullptr)
	{
		pUIManager = new UIManager;
	}
	return pUIManager;
}

void PKH::UIManager::Destroy()
{
	if (pUIManager)
	{
		delete pUIManager;
		pUIManager = nullptr;
	}
}

PKH::UIManager::UIManager()
{
}

PKH::UIManager::~UIManager()
{
	Release();
}

HRESULT PKH::UIManager::Initialize()
{
	return pUIManager->Ready();
}

HRESULT PKH::UIManager::Ready()
{
	pPlayerInfoPanel = PlayerInfoPanel::GetInstance();

	return S_OK;
}

void PKH::UIManager::Update()
{
	if(pUIManager->pPlayerInfoPanel) pUIManager->pPlayerInfoPanel->Update();
}

void PKH::UIManager::Release()
{
	pUIManager->pPlayerInfoPanel = nullptr;
	PlayerInfoPanel::GetInstance()->DestroyInstance();
}
