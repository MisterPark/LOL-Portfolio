#include "stdafx.h"
#include "LoadingScene.h"
#include "Label.h"
#include "TestScene.h"

long loadCount = 0;


void LoadingScene::OnLoaded()
{
	Camera::GetInstance()->SetPosition(Vector3(0, 0, 0));
	Camera::GetInstance()->transform->look = Vector3(0, 0, 1);

	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/character/malphite/", L"malp.X", Count);

	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/blitzcrank/", L"blitzcrank.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/darius/", L"darius.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/diana/", L"diana.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/garen/", L"garen.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/leesin/", L"leesin.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/missfortune/", L"missfortune.X", Count);

	//LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/sr/", L"sr.x", Count);
	LoadManager::LoadTerrainMeshAsync(L"Resource/Mesh/summoner_rift/", L"summoner_rift.x",Count);
	LoadManager::LoadNavMeshAsync(L"Resource/Mesh/nav/", L"summoner_rift_nav.x", Count);
	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/nav/", L"nav_wall.x", Count);

	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/turret_order/", L"turret_order.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/turret_order/", L"sruap_orderturret1_break1.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/turret_order/", L"sruap_orderturret1_break2.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/turret_order/", L"sruap_orderturret1_break3.x", Count);
}

void LoadingScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void LoadingScene::Update()
{
	
	if (loadCount == 14)
	{

		SceneManager::LoadScene<TestScene>();
	}
}

void LoadingScene::Count()
{
	_InterlockedIncrement(&loadCount);
}
