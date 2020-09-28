#include "stdafx.h"
#include "MainGame.h"

using namespace PKH;

PKH::MainGame* pMainGame = nullptr;

PKH::MainGame::MainGame()
{
}

PKH::MainGame::~MainGame()
{
}

PKH::MainGame* MainGame::GetInstance()
{
    if (pMainGame == nullptr)
    {
        pMainGame = new MainGame;
    }
    
    return pMainGame;
}

void PKH::MainGame::Destroy()
{
    if (pMainGame)
    {
        delete pMainGame;
        pMainGame = nullptr;
    }
}

void PKH::MainGame::Initialize()
{
    // 다른 모든 매니저 초기화
	TimeManager::GetInstance();
	TimeManager::SetFPS(60.f);
	D2DRenderManager::GetInstance();
	CollisionManager::GetInstance();
	InputManager::GetInstance();
	ObjectManager::GetInstance();
	//RenderManager::GetInstance();

	SceneManager::GetInstance();

	Camera::GetInstance();
	FileManager::GetInstance();

	SoundManager::GetInstance()->Initialize();

    // 리소스 로드

	pMainGame->tri = new Triangle;
}

void PKH::MainGame::Release()
{
    // 다른 모든 매니저 해제
	SceneManager::Destroy();
	TimeManager::Destroy();
	ObjectManager::Destroy();
	//RenderManager::Release();
	D2DRenderManager::Destroy();
	InputManager::Destroy();
	CollisionManager::Destroy();
	Camera::Destroy();
	FileManager::Destroy();

	SoundManager::Destroy();
}

void PKH::MainGame::Update()
{
	InputManager::Update();
	ObjectManager::Update();
	//Camera::Update();
	CollisionManager::Update();
	ObjectManager::PostUpdate();

	if (!TimeManager::SkipFrame())
	{
		D2DRenderManager::Clear();

		ObjectManager::PreRender();
		ObjectManager::Render();
		ObjectManager::PostRender();

		pMainGame->tri->Render();

		D2DRenderManager::Present();
	}

	SceneManager::Update();
}

void PKH::MainGame::Pause()
{
}

void PKH::MainGame::Resume()
{
}

void PKH::MainGame::Shutdown()
{
}
