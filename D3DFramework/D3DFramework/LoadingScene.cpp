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
}

void LoadingScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void LoadingScene::Update()
{
	
	if (loadCount == 1)
	{
		SceneManager::LoadScene<TestScene>();
	}
}

void LoadingScene::Count()
{
	_InterlockedIncrement(&loadCount);
}
