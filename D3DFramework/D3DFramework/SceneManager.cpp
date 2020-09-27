#include "stdafx.h"
#include "SceneManager.h"

using namespace PKH;

PKH::SceneManager* pSceneManager = nullptr;

PKH::SceneManager::SceneManager()
{

}
PKH::SceneManager::~SceneManager()
{
	if (pCurrentScene != nullptr)
	{
		pCurrentScene->OnUnloaded();
		delete pCurrentScene;
	}
	if (pReadyScene != nullptr)
	{
		delete pReadyScene;
	}
}

void PKH::SceneManager::LoadScene(IScene * pScene)
{
	auto& self = *pSceneManager;
	if (self.pReadyScene != nullptr)
	{
		delete self.pReadyScene;
	}
	self.pReadyScene = pScene;
}

SceneManager* PKH::SceneManager::GetInstance()
{
	if (pSceneManager == nullptr)
	{
		pSceneManager = new SceneManager();
	}
	return pSceneManager;
}


void PKH::SceneManager::Destroy()
{
	delete pSceneManager;
}

void PKH::SceneManager::Update()
{
	auto& self = *pSceneManager;
	if (self.pReadyScene != nullptr)
	{
		IScene* pReadyScene = self.pReadyScene;
		self.pReadyScene = nullptr;
		if (self.pCurrentScene != nullptr)
		{
			self.pCurrentScene->OnUnloaded();
			delete self.pCurrentScene;
		}
		self.pCurrentScene = pReadyScene;
		self.pCurrentScene->OnLoaded();
	}
	if (self.pCurrentScene)
	{
		self.pCurrentScene->Update();
	}
}

