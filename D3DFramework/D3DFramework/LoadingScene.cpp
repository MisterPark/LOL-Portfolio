#include "stdafx.h"
#include "LoadingScene.h"
#include "Label.h"
#include "TestScene.h"

long loadCount = 0;

void LoadingScene::OnLoaded()
{
	Camera::GetInstance()->SetPosition(Vector3(0, 0, 0));
	Camera::GetInstance()->transform->look = Vector3(0, 0, 1);

	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/malphite/", L"malp.X", Count);

	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/garen/", L"garen.X", Count);

	//LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/sr/", L"sr.x", Count);
	LoadManager::LoadTerrainMeshAsync(L"Resource/Mesh/summoner_rift/", L"summoner_rift.x",Count);
	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/nav/", L"summoner_rift_nav.x", Count);
}

void LoadingScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void LoadingScene::Update()
{
	
	if (loadCount == 4)
	{

		SceneManager::LoadScene<TestScene>();
	}
}

void LoadingScene::Count()
{
	_InterlockedIncrement(&loadCount);
}
