#include "stdafx.h"
#include "LoadManager.h"

LoadManager* pLoadManager = nullptr;

LoadManager::LoadManager()
{
	pRenderMgr = RenderManager::GetInstance();
	isFinish = false;
	percent = 0.f;
	text = L"";
}

LoadManager::~LoadManager()
{
    Release();
}

LoadManager* LoadManager::GetInstance()
{
    if (pLoadManager == nullptr)
    {
        pLoadManager = new LoadManager;
    }
    return pLoadManager;
}

void LoadManager::Destroy()
{
    if (pLoadManager)
    {
        delete pLoadManager;
        pLoadManager = nullptr;
    }
}

void LoadManager::Initialize()
{
	if (pLoadManager->hThread != INVALID_HANDLE_VALUE)
		CloseHandle(pLoadManager->hThread);
	pLoadManager->isFinish = false;
	pLoadManager->percent = 0.f;
	pLoadManager->text = L"";
}

void LoadManager::Release()
{
    //WaitForSingleObject(pLoadManager->hThread, INFINITE);
    CloseHandle(pLoadManager->hThread);
}

bool LoadManager::IsFinish()
{
    return pLoadManager->isFinish;
}

float LoadManager::GetProgress()
{
    return pLoadManager->percent;
}

wstring LoadManager::GetText()
{
    return pLoadManager->text;
}

unsigned int __stdcall LoadManager::LodingThread(void* arg)
{
    LoadManager* loadManager = (LoadManager*)arg;
    
    loadManager->LoadAll();
    
    return 0;
}

void LoadManager::LoadResources()
{
    pLoadManager->hThread = (HANDLE)_beginthreadex(NULL, 0, LodingThread, pLoadManager, 0, nullptr);

}

void LoadManager::LoadAll()
{
	
}



