#include "stdafx.h"
#include "SceneManager.h"

using namespace Engine;

Engine::SceneManager* pSceneManager = nullptr;

Engine::SceneManager::SceneManager()
{

}
Engine::SceneManager::~SceneManager()
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

void Engine::SceneManager::LoadScene(Scene * pScene)
{
	auto& self = *pSceneManager;
	if (self.pReadyScene != nullptr)
	{
		delete self.pReadyScene;
	}
	self.pReadyScene = pScene;
}

SceneManager* Engine::SceneManager::GetInstance()
{
	if (pSceneManager == nullptr)
	{
		pSceneManager = new SceneManager();
	}
	return pSceneManager;
}


void Engine::SceneManager::Destroy()
{
	delete pSceneManager;
}

void Engine::SceneManager::Update()
{
	auto& self = *pSceneManager;
	if (self.pReadyScene != nullptr)
	{
		Scene* pReadyScene = self.pReadyScene;
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

void Engine::SceneManager::PostUpdate()
{
	auto& self = *pSceneManager;
	if (self.pCurrentScene)
	{
		self.pCurrentScene->PostUpdate();
	}
}

Scene* Engine::SceneManager::GetCurrentScene()
{
	return pSceneManager->pCurrentScene;
}

