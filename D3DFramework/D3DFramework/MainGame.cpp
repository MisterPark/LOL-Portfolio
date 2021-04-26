#include "stdafx.h"
#include "MainGame.h"
#include "TestScene.h"
#include "SkyBox.h"
#include "TitleScene.h"
#include "LoadingScene.h"
#include "TestLoadingScene.h"
#include "RenderSystem.h"
#include <io.h>

using namespace Engine;

Engine::MainGame* pMainGame = nullptr;

Engine::MainGame::MainGame()
{
}

Engine::MainGame::~MainGame()
{
}

Engine::MainGame* MainGame::GetInstance()
{
    if (pMainGame == nullptr)
    {
        pMainGame = new MainGame;
    }
    
    return pMainGame;
}

void Engine::MainGame::Destroy()
{
    if (pMainGame)
    {
        delete pMainGame;
        pMainGame = nullptr;
    }
}

void Engine::MainGame::Initialize(int screenW, int screenH)
{
	pMainGame->width = screenW;
	pMainGame->height = screenH;
	
	Network::GetInstance();
	Network::Initialize();
	Random::InitState();

	// 다른 모든 매니저 초기화
	Time::GetInstance();
	Time::SetFPS(60);
	
	RenderManager::GetInstance();
	RenderManager::Initialize(screenW, screenH);

	LoadUISprite();

	CollisionManager::GetInstance();
	LightManager::GetInstance();
	Input::GetInstance();
	SkyBox::GetInstance();

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

	ItemManager::GetInstance()->Initialize();

	// 씬로드
	SceneManager::LoadScene<TestLoadingScene>();
	//SceneManager::LoadScene<LoadingScene>();
	//SceneManager::LoadScene<TestScene>();
}

void Engine::MainGame::Update()
{
	// 1. 인풋 먼저
	Input::Update();

	UI::SetPointerOverUI(false);
	SceneManager::PreUpdate();
	SceneManager::Update();

	Cursor::GetInstance()->Update();

	Camera::GetInstance()->Update();
	SkyBox::GetInstance()->Update();
	Frustum::Update();
	
	CollisionManager::GetInstance()->Update();
	SceneManager::PostUpdate();
	SoundManager::Update();

	Time::SkipFrame();

	RenderSystem::Render();
}

void Engine::MainGame::Release()
{
	// 다른 모든 매니저 해제
	LoadManager::Destroy();
	SceneManager::Destroy();
	Time::Destroy();
	CollisionManager::Destroy();
	SkyBox::Destroy();
	UIManager::DestroyInstance();
	RenderSystem::Destory();
	RenderManager::Destroy();
	Input::Destroy();
	Camera::Destroy();
	FileManager::Destroy();
	LightManager::Destroy();
	SoundManager::Destroy();
	Cursor::Destroy();
	LobbyWindow::Destroy();
	Network::Destroy();
	Frustum::Destroy();
	NavNodeManager::Destroy();
	ItemManager::Destroy();
}

void Engine::MainGame::Pause()
{
}

void Engine::MainGame::Resume()
{
}

void Engine::MainGame::Shutdown()
{
	PostQuitMessage(0);
}

int Engine::MainGame::GetWidth()
{
	return pMainGame->width;
}

int Engine::MainGame::GetHeight()
{
	return pMainGame->height;
}


void Engine::MainGame::LoadUISprite()
{
	// 리소스 로드
	//RenderManager::LoadSprite(TextureKey::UI_CURSOR, L"Texture\\UI\\Cursor.png");
	//RenderManager::LoadSprite(TextureKey::GRASS, L"Resource\\Texture\\grassTexture.png");
	RenderManager::LoadSprite(L"Resource\\Texture\\", L"Empty.png");
	RenderManager::LoadSprite(L"Resource\\Texture\\", L"red.png");
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
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_big_red.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"bar_big_marker.png");

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

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"skilllevel_on.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"skilllevel_off.png");

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
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_panel (1)_hover.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_panel (1)_pressed.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_panel (2).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_panel (3).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_panel (4).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_panel (5).png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"stat_panel (5)_icon.png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"item_outline.png");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"item_outline_selected.png");

	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"icon_spell_summonerspell_recall_01.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"baron_recall.dds");
	RenderManager::LoadSprite(L"Resource\\UI\\HUD\\", L"textbox.png");

	// Itemshop
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_background.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_buy_default.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_buy_disabled.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_buy_hover.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_buy_pressed.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_close_default.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_close_hover.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_close_pressed.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_disabled.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_pressed.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_restore_default.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_restore_hover.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_sel_default.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_button_sel_hover.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_item_outline.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_selecteditem.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_hoveritem.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"itemshop_blankslot.png");
	RenderManager::LoadSprite(L"Resource\\UI\\itemshop\\", L"icon_gold.png");


	LoadAllTextureInFolder(L"Resource\\UI\\item\\", L"*.dds");
	LoadAllTextureInFolder(L"Resource\\UI\\buff\\", L"*.dds");
	LoadAllTextureInFolder(L"Resource\\Mesh\\character\\missfortune\\particles\\", L"*.dds");
	LoadAllTextureInFolder(L"Resource\\Mesh\\character\\garen\\particles\\", L"*.dds");

	// scoreboard
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_mainpanel.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_champborder_alive.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_champborder_dead.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dead.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_playermark.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_mia.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_itemempty.png");

	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragoncount_break.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragoncount_wind.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragoncount_fire.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragoncount_earth.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragoncount_water.png");

	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragonsimbol_default.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragonsimbol_wind_1.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragonsimbol_wind_2.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragonsimbol_fire_1.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragonsimbol_fire_2.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragonsimbol_earth_1.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragonsimbol_earth_2.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragonsimbol_water_1.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_dragonsimbol_water_2.png");

	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_mobtimepanel.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_heraldtimepanel.png");

	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_simbol_blue.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_simbol_red.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_simbol_dragon_wind.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_simbol_dragon_fire.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_simbol_dragon_earth.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_simbol_dragon_ocean.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_simbol_dragon_elder.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_simbol_baron.png");
	RenderManager::LoadSprite(L"Resource\\UI\\scoreboard\\", L"scoreboard_simbol_riftherald.png");

	// summoner spell
	RenderManager::LoadSprite(L"Resource\\UI\\summoner\\", L"summoner_boost.png");
	RenderManager::LoadSprite(L"Resource\\UI\\summoner\\", L"summoner_exhaust.png");
	RenderManager::LoadSprite(L"Resource\\UI\\summoner\\", L"summoner_flash.png");
	RenderManager::LoadSprite(L"Resource\\UI\\summoner\\", L"summoner_haste.png");
	RenderManager::LoadSprite(L"Resource\\UI\\summoner\\", L"summoner_heal.png");
	RenderManager::LoadSprite(L"Resource\\UI\\summoner\\", L"summoner_smite.png");
	RenderManager::LoadSprite(L"Resource\\UI\\summoner\\", L"summoner_teleport.png");
	RenderManager::LoadSprite(L"Resource\\UI\\summoner\\", L"summonerbarrier.png");
	RenderManager::LoadSprite(L"Resource\\UI\\summoner\\", L"summonerignite.png");
	RenderManager::LoadSprite(L"Resource\\UI\\summoner\\", L"summonermana.png");

	// tooltip
	LoadAllTextureInFolder(L"Resource\\UI\\tooltip\\", L"*.png");

	// end of game
	LoadAllTextureInFolder(L"Resource\\UI\\endofgame\\", L"*.png");
	LoadAllTextureInFolder(L"Resource\\UI\\endofgame\\", L"*.dds");


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

void Engine::MainGame::LoadAllTextureInFolder(const wstring& _path, const wstring& _filter)
{
	char _cPath[MAX_PATH] = {};
	WideCharToMultiByte(CP_ACP, 0, _path.c_str(), _path.length(), _cPath, _path.length(), NULL, NULL);

	char _cFilter[MAX_PATH] = {};
	WideCharToMultiByte(CP_ACP, 0, _filter.c_str(), _filter.length(), _cFilter, _filter.length(), NULL, NULL);

	_finddata_t fd;
	char path[1024] = {};
	_fullpath(path, _cPath, 1024);
	strcat_s(path, _cFilter);
	long handle = _findfirst(path, &fd);
	if (handle != -1)
	{
		do {
			string name = fd.name;
			//std::wstring file(fd.name, &fd.name[260]);
			wstring file;
			file.assign(name.begin(), name.end());
			RenderManager::LoadSprite(_path.c_str(), file);
		} while (_findnext(handle, &fd) != -1);
		_findclose(handle);
	}
}
