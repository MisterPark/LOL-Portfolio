#include "stdafx.h"
#include "LightManager.h"

LightManager* pLightManager = nullptr;

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
}

LightManager* LightManager::GetInstance()
{
    if (pLightManager == nullptr)
    {
        pLightManager = new LightManager;
    }
    return pLightManager;
}

void LightManager::Destroy()
{
    if (pLightManager)
    {
        delete pLightManager;
        pLightManager = nullptr;
    }
}

void LightManager::RegisterObject(Light* pLight)
{
    pLightManager->lightList.push_back(pLight);
}

void LightManager::DisregisterObject(Light* pLight)
{
    pLightManager->lightList.remove(pLight);
}
