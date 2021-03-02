#include "stdafx.h"
#include "TitleScene.h"

void TitleScene::OnLoaded()
{
	Cursor::Show();
	//SoundManager::PlayBGM(L"Title.wav");

	Camera::GetInstance()->SetPosition(Vector3(0, 0, 0));
	Camera::GetInstance()->transform->look = Vector3(0, 0, 1);
}

void TitleScene::OnUnloaded()
{
}

void TitleScene::Update()
{
	Scene::Update();
}
