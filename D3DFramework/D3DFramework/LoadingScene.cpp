#include "stdafx.h"
#include "LoadingScene.h"
#include "Stage_Opening.h"
#include "Label.h"
#include "ProgressBar.h"
#include "UI_Title.h"
#include "EndingScene.h"

void LoadingScene::OnLoaded()
{
	Camera::GetInstance()->SetPosition(Vector3(0, 0, 0));
	Camera::GetInstance()->transform->look = Vector3(0, 0, 1);

	// UI
	UI_Title* title = (UI_Title*)ObjectManager::GetInstance()->CreateObject<UI_Title>();
	title->SetTexture(TextureKey::UI_LOADING_SCREEN);

	label = (Label*)ObjectManager::GetInstance()->CreateObject<Label>();
	label->transform->scale = { 2,2,2 };
	//label->text = L"Å×½ºÆ®";
	bar = (ProgressBar*)ObjectManager::GetInstance()->CreateObject<ProgressBar>();
	bar->transform->position = { 400,20,0 };
	bar->transform->scale = { 0.6f,0.6f, 0.6f };

	

	LoadManager::LoadResources();

	
}

void LoadingScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void LoadingScene::Update()
{
	if (label != nullptr)
	{
		label->text = LoadManager::GetText();
	}

	if (bar != nullptr)
	{
		bar->progress = LoadManager::GetProgress();
	}

	if (LoadManager::IsFinish())
	{
		
		if (InputManager::GetKeyDown(VK_RETURN))
		{
			SceneManager::LoadScene<Stage_Opening>();
			//SceneManager::LoadScene<EndingScene>();
		}
	}
}
