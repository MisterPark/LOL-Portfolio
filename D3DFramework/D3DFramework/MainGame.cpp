#include "stdafx.h"
#include "MainGame.h"
#include "TestScene.h"
#include "SkyBox.h"
#include "TitleScene.h"
#include "LoadingScene.h"
#include "TestLoadingScene.h"

#include "RenderSystem.h"
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

void PKH::MainGame::Initialize(int screenW, int screenH)
{
	pMainGame->width = screenW;
	pMainGame->height = screenH;
	
	Network::GetInstance();
	Network::Initialize();
	//LobbyWindow::GetInstance();
	Random::InitState();

	// 다른 모든 매니저 초기화
	TimeManager::GetInstance();
	TimeManager::SetFPS(300);
	
	RenderManager::GetInstance();
	RenderManager::Initialize(screenW, screenH);

	LoadUISprite();

	ObjectManager::GetInstance();
	CollisionManager::GetInstance();
	LightManager::GetInstance();
	InputManager::GetInstance();
	SkyBox::GetInstance();

	//RenderManager::GetInstance();

	SceneManager::GetInstance();

	Camera::GetInstance();
	FileManager::GetInstance();
	Cursor::GetInstance();

	SoundManager::GetInstance()->Initialize();
	LoadManager::GetInstance();
	Frustum::GetInstance();
	NavNodeManager::GetInstance();

	RenderSystem::Initialize();

	UIManager::GetInstance();

	//SkillManager::GetInstance();

	// 씬로드
	SceneManager::LoadScene<TestLoadingScene>();
	//SceneManager::LoadScene<LoadingScene>();
	//SceneManager::LoadScene<TestScene>();
}

void PKH::MainGame::Update()
{
	// 1. 인풋 먼저
	InputManager::Update();

	// 2. 씬 매니저 업데이트
	SceneManager::Update();

	// 3. Player 업데이트

	// 4. Obj 업데이트
	ObjectManager::Update();
	Cursor::GetInstance()->Update();

	Camera::GetInstance()->Update();
	SkyBox::GetInstance()->Update();
	Frustum::Update();
	
	CollisionManager::GetInstance()->Update();
	ObjectManager::PostUpdate();
	SoundManager::Update();

#if 0
	if (!TimeManager::SkipFrame())
	{
		RenderManager::Clear();
		RenderSystem::Render();
		RenderManager::Present();
	}
#else
	TimeManager::SkipFrame();

	RenderManager::Clear();
	RenderSystem::Render();
	RenderManager::Present();
#endif
}

void PKH::MainGame::Release()
{
	// 다른 모든 매니저 해제
	LoadManager::Destroy();
	SceneManager::Destroy();
	TimeManager::Destroy();
	ObjectManager::Destroy();
	CollisionManager::Destroy();
	SkyBox::Destroy();
	//RenderManager::Release();
	UIManager::DestroyInstance();
	RenderSystem::Destory();
	RenderManager::Destroy();
	InputManager::Destroy();
	Camera::Destroy();
	FileManager::Destroy();
	LightManager::Destroy();
	SoundManager::Destroy();
	Cursor::Destroy();
	LobbyWindow::Destroy();
	Network::Destroy();
	Frustum::Destroy();
	NavNodeManager::Destroy();
}

void PKH::MainGame::Pause()
{
}

void PKH::MainGame::Resume()
{
}

void PKH::MainGame::Shutdown()
{
	PostQuitMessage(0);
}

int PKH::MainGame::GetWidth()
{
	return pMainGame->width;
}

int PKH::MainGame::GetHeight()
{
	return pMainGame->height;
}


void PKH::MainGame::LoadUISprite()
{
	// 리소스 로드
	//RenderManager::LoadSprite(TextureKey::UI_CURSOR, L"Texture\\UI\\Cursor.png");
	//RenderManager::LoadSprite(TextureKey::GRASS, L"Resource\\Texture\\grassTexture.png");
	RenderManager::LoadSprite(L"Resource\\Texture\\", L"Empty.png");
	RenderManager::LoadSprite(L"Resource\\UI\\cursor\\", L"hover_precise.tga");
	RenderManager::LoadSprite(L"Resource\\UI\\cursor\\", L"singletarget.tga");
	//로딩씬
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"srbackground.dds");

	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"loadingscreen_spinner_atlas.dds",8,4);
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"loadingFrameBlue.png");
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"loadingFrameRed.png");
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"loadScreen.png");

	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"ahriloadscreen.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"amumuloadscreen.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"blitzcrankloadscreen.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"dariusloadscreen.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"dianaloadscreen.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"garenloadscreen.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"jaxloadscreen.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"jinxloadscreen.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"leesinloadscreen.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"leonaloadscreen.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\loading\\", L"missfortuneloadscreen.dds");

	RenderManager::LoadSprite(L"Resource\\Spell\\icon\\", L"summoner_barrier.dds");
	RenderManager::LoadSprite(L"Resource\\Spell\\icon\\", L"summoner_boost.dds");
	RenderManager::LoadSprite(L"Resource\\Spell\\icon\\", L"summoner_exhaust.dds");
	RenderManager::LoadSprite(L"Resource\\Spell\\icon\\", L"summoner_flash.dds");
	RenderManager::LoadSprite(L"Resource\\Spell\\icon\\", L"summoner_haste.dds");
	RenderManager::LoadSprite(L"Resource\\Spell\\icon\\", L"summoner_heal.dds");
	RenderManager::LoadSprite(L"Resource\\Spell\\icon\\", L"summoner_ignite.dds");
	RenderManager::LoadSprite(L"Resource\\Spell\\icon\\", L"summoner_mana.dds");
	RenderManager::LoadSprite(L"Resource\\Spell\\icon\\", L"summoner_smite.dds");
	RenderManager::LoadSprite(L"Resource\\Spell\\icon\\", L"summoner_teleport.dds");
	
	// 인게임
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_big1.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_big2.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_big3.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_big4.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_exp.png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_float (1).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_float (2).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_float (3).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_float (4).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_float (5).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_float (6).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_float (7).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_float (8).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_float (9).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_float (10).png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_small (1).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_small (2).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_small (3).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_small (4).png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_tip (1).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_tip (2).png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_float (1).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_float (2).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_float (3).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_float (4).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_float (5).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_float (6).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_float (7).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_float (8).png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_skill (1).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_skill (2).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_skill (3).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_skill (4).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_skill (5).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"border_skill (6).png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"button_gold (1).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"button_gold (2).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"button_gold (3).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"button_gold (4).png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"button_skillup (1).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"button_skillup (2).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"button_skillup (3).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"button_skillup (4).png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"hud_icon (1).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"hud_icon (2).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"hud_icon (3).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"hud_icon (4).png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"map11.png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"minimapBorder.png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"panel (1).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"panel (2).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"panel (3).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"panel (4).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"panel (5).png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (1).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (2).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (3).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (4).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (5).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (6).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (7).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (8).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (9).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (10).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (11).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (12).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (13).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (14).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (15).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_icon (16).png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_panel (1).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_panel (2).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_panel (3).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_panel (4).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_panel (5).png");

	// Itemshop
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_background.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_sel_default.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_restore_default.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_buy_default.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_item_outline.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_close_default.png");

	RenderManager::LoadSprite(L"Resource\\UI\\item\\", L"1001_class_t1_bootsofspeed.dds");


	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"ahri_circle.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"ahri_square.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"amumu_circle.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"amumu_square.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"blitzcrank_circle.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"blitzcrank_square.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"darius_circle.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"darius_square.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"diana_circle.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"diana_square.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"garen_circle.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"garen_square.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"jax_circle.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"jax_square.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"jinx_circle.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"jinx_square.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"leesin_circle.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"leesin_square.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"leona_circle.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"leona_square.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"missfortune_circle.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\champ\\", L"missfortune_square.png");

	RenderManager::LoadSprite(L"Resource\\UI\\champ\\ahri\\", L"ahri_q.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\ahri\\", L"ahri_w.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\ahri\\", L"ahri_e.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\ahri\\", L"ahri_r.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\ahri\\", L"ahri_passive.dds");

	RenderManager::LoadSprite(L"Resource\\UI\\champ\\blitzcrank\\", L"blitzcrank_q.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\blitzcrank\\", L"blitzcrank_w.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\blitzcrank\\", L"blitzcrank_e.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\blitzcrank\\", L"blitzcrank_r.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\blitzcrank\\", L"blitzcrank_passive.dds");

	RenderManager::LoadSprite(L"Resource\\UI\\champ\\darius\\", L"darius_q.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\darius\\", L"darius_w.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\darius\\", L"darius_e.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\darius\\", L"darius_r.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\darius\\", L"darius_passive.dds");

	RenderManager::LoadSprite(L"Resource\\UI\\champ\\diana\\", L"diana_q.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\diana\\", L"diana_w.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\diana\\", L"diana_e.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\diana\\", L"diana_r.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\diana\\", L"diana_passive.dds");

	RenderManager::LoadSprite(L"Resource\\UI\\champ\\garen\\", L"garen_q.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\garen\\", L"garen_w.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\garen\\", L"garen_e1.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\garen\\", L"garen_e2.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\garen\\", L"garen_r.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\garen\\", L"garen_passive.dds");

	RenderManager::LoadSprite(L"Resource\\UI\\champ\\jax\\", L"jax_q.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\jax\\", L"jax_w.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\jax\\", L"jax_e.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\jax\\", L"jax_r.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\jax\\", L"jax_passive.dds");

	RenderManager::LoadSprite(L"Resource\\UI\\champ\\jinx\\", L"jinx_q1.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\jinx\\", L"jinx_q2.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\jinx\\", L"jinx_w.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\jinx\\", L"jinx_e.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\jinx\\", L"jinx_r.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\jinx\\", L"jinx_passive.dds");

	RenderManager::LoadSprite(L"Resource\\UI\\champ\\leesin\\", L"leesin_q.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\leesin\\", L"leesin_w.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\leesin\\", L"leesin_e.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\leesin\\", L"leesin_r.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\leesin\\", L"leesin_passive.dds");

	RenderManager::LoadSprite(L"Resource\\UI\\champ\\leona\\", L"leona_q.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\leona\\", L"leona_w.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\leona\\", L"leona_e.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\leona\\", L"leona_r.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\leona\\", L"leona_passive.dds");

	RenderManager::LoadSprite(L"Resource\\UI\\champ\\missfortune\\", L"missfortune_q.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\missfortune\\", L"missfortune_w.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\missfortune\\", L"missfortune_e.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\missfortune\\", L"missfortune_r.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\champ\\missfortune\\", L"missfortune_passive.dds");

	// 인디케이터
	RenderManager::LoadSprite(L"Resource\\Spell\\indicator\\", L"circularrangeindicator.png");

	// 터렛
	RenderManager::LoadSprite(L"Resource\\Mesh\\turret_order\\", L"sru_chaos_cm_ba_mis_tex.dds");
	RenderManager::LoadSprite(L"Resource\\Mesh\\turret_order\\", L"sru_chaos_cm_ba_mis_tex_blue.dds");

}										
