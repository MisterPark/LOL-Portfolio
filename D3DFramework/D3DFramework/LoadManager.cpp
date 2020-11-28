#include "stdafx.h"
#include "LoadManager.h"

LoadManager* pLoadManager = nullptr;

LoadManager::LoadManager()
{
    Initialize();
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
    InitializeCriticalSection(&csQ[0]);
    InitializeCriticalSection(&csQ[1]);
    InitializeCriticalSection(&csQ[2]);
    for (int i = 0; i < dfMaxThreadCount; i++)
    {
        threadInfo[i].number = i;
        threadInfo[i].pLoad = this;
        threadInfo[i].shutdownFlag = false;
        hThread[i] = (HANDLE)_beginthreadex(NULL, 0, LodingThread, &threadInfo[i], 0, nullptr);
    }
}

void LoadManager::Release()
{
    
    for (int i = 0; i < dfMaxThreadCount; i++)
    {
        threadInfo[i].shutdownFlag = true;
    }
    WaitForMultipleObjects(dfMaxThreadCount, hThread, TRUE, INFINITE);
    for (int i = 0; i < dfMaxThreadCount; i++)
    {
        CloseHandle(pLoadManager->hThread[i]);
    }
    DeleteCriticalSection(&csQ[0]);
    DeleteCriticalSection(&csQ[1]);
    DeleteCriticalSection(&csQ[2]);
    
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
    ThreadInfo* info = (ThreadInfo*)arg;
    UINT number = info->number;

    printf("[DEBUG] [%d]번 스레드 가동\n", info->number);
    
    while (!info->shutdownFlag)
    {
        if (info->pLoad->jobQ[number].size() == 0)
        {
            info->isWorking = false;
            Sleep(0);
            continue;
        }
        
        info->isWorking = true;
        EnterCriticalSection(&info->pLoad->csQ[number]);
        LoadingElement elem = info->pLoad->jobQ[number].front();
        info->pLoad->jobQ[number].pop();

        switch (elem.type)
        {
        case LoadType::STATIC_MESH:
        {
            RenderManager::LoadStaticMesh(elem.filePath.c_str(), elem.fileName.c_str());
            break;
        }
        case LoadType::DYNAMIC_MESH:
        {
            RenderManager::LoadDynamicMesh(elem.filePath.c_str(), elem.fileName.c_str());
            break;
        }
            
        default:
            break;
        }
        
        LeaveCriticalSection(&info->pLoad->csQ[number]);
        
        if (elem.Callback != nullptr)
        {
            elem.Callback();
        }
    }
    
    printf("[DEBUG] [%d]번 스레드 종료\n", info->number);
    return 0;
}


UINT LoadManager::FindUnemployedThread()
{
    int size = 0;
    int minSize = INT_MAX;
    int index = 0;
    bool findUnemplement = false;

    for (int i = 0; i < dfMaxThreadCount; i++)
    {
        if (pLoadManager->threadInfo[i].isWorking == false)
        {
            index = i;
            findUnemplement = true;
            break;
        }
    }

    if (findUnemplement == false)
    {
        for (int i = 0; i < dfMaxThreadCount; i++)
        {
            size = pLoadManager->jobQ[i].size();
            if (size < minSize)
            {
                index = i;
                minSize = size;
            }
        }
    }
    
    return index;
}

void LoadManager::LoadStaticMeshAsync(const wstring& filePath, const wstring& fileName, void(*Callback)())
{
    UINT index = FindUnemployedThread();

    LoadingElement elem;
    elem.filePath = filePath;
    elem.fileName = fileName;
    elem.type = LoadType::STATIC_MESH;
    elem.Callback = Callback;

    EnterCriticalSection(&pLoadManager->csQ[index]);

    pLoadManager->jobQ[index].push(elem);

    LeaveCriticalSection(&pLoadManager->csQ[index]);
}

void LoadManager::LoadDynamicMeshAsync(const wstring& filePath, const wstring& fileName, void(*Callback)())
{
    UINT index = FindUnemployedThread();

    LoadingElement elem;
    elem.filePath = filePath;
    elem.fileName = fileName;
    elem.type = LoadType::DYNAMIC_MESH;
    elem.Callback = Callback;

    EnterCriticalSection(&pLoadManager->csQ[index]);

    pLoadManager->jobQ[index].push(elem);

    LeaveCriticalSection(&pLoadManager->csQ[index]);
}



