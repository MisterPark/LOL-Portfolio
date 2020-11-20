#include "stdafx.h"
#include "LodingScene.h"
#include "TestScene.h"

int resourceCount = 0;

void LodingScene::OnLoaded()
{
	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/malphite/", L"malp.X", Count);
}

void LodingScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void LodingScene::Update()
{
	if (resourceCount == 1)
	{
		SceneManager::LoadScene<TestScene>();
	}
	
}

void LodingScene::Count()
{
	resourceCount++;
}
