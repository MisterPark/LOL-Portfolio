#include "stdafx.h"
#include "TestLoadingScene.h"
#include "TestScene.h"
#include "LoadingBackGround.h"
#include "LoadingBorder.h"
#include "LoadingPanel.h"
#include "UI_Spell.h"
#include "LoadingChampPanel.h"
#include "LoadingChampScreen.h"
#include "Label.h"
#include "TestScene2.h"

// TODO : 테스트 끝나면 빼기
#include "AnnouncerPanel.h"

//C++17이전에서는 filesystem은 experimental이다. 일단 호환성을 위해 이렇게 해둠.
#if __cplusplus < 20200000L
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental\filesystem>
namespace std
{
	namespace filesystem
	{
		using namespace std::experimental::filesystem;
	}
}
#else
#include <filesystem>
#endif

long resourceMax = 0;
long resourceLoadCnt = 0;

void TestLoadingScene::OnLoaded()
{
	int screenW = MainGame::GetWidth();
	int screenH = MainGame::GetHeight();
	
	int borderW = screenW / 8;
	int padding = borderW / 4;
	int borderH = (screenH - borderW )/2;

	float ratioX = (float)borderW / 308;
	float ratioY = (float)borderH / 560;

	int spellW = (int)(30 * ratioX);
	int spellH = (int)(30 * ratioY);
	int spell1offsetX = (int)(25 * ratioX);
	int spell2offsetX = (int)(64 * ratioX);
	int spelloffsetY = (int)(488 * ratioY);
	int nameOffsetX = (int)(153 * ratioX);
	int champNameOffsetY = (int)(430 * ratioY);
	int nickNameOffsetY = (int)(525 * ratioY);

	Camera::GetInstance()->SetPosition(Vector3(0, 0, -1));
	Camera::GetInstance()->transform->look = Vector3(0, 0, 1);

	Cursor::GetInstance()->Show();

	SceneManager::GetCurrentScene()->CreateObject<LoadingBackGround>(Layer::UI);
	for (int i = 0; i < 10; ++i) {
		screens[i] = new LoadingChampScreen();
		UIManager::GetInstance()->AddUI(screens[i]);
	}

#if 1 // TODO : 임시 코드니까 다되면 꼭 빼야됨
	//UIManager::GetInstance()->AddUI(AnnouncerPanel::GetInstance());
	//AnnouncerPanel::GetInstance()->AddAnnouncer(L"소환사의 협곡에 오신 것을 환영합니다", Team::BLUE);
	//AnnouncerPanel::GetInstance()->AddAnnouncer(L"선취점!", Team::BLUE, L"garen_circle");
	//AnnouncerPanel::GetInstance()->AddAnnouncer(L"적의 포탑이 파괴되었습니다!", Team::BLUE, L"garen_circle", L"turret_red_square");
#endif

	CreateChampPanel(borderW, borderH, padding);

	LoadResources();
}

void TestLoadingScene::OnUnloaded()
{
	UIManager::GetInstance()->DeleteListAll();
}

void TestLoadingScene::Update()
{
	Scene::Update();
	int loadPercent =  (int)(((float)resourceLoadCnt / resourceMax) * 100);
	screens[0]->progressLabel->SetText(L"%d%%", loadPercent);

	if (resourceLoadCnt == resourceMax)
	{
		SceneManager::LoadScene<TestScene>();
		//SceneManager::LoadScene<TestScene2>();
	}
}

void TestLoadingScene::LoadResources()
{
	LoadStaticMeshAsync(L"Resource/Mesh/character/malphite/malp.X");
	
	// 오브젝트
	LoadDynamicMeshAsync(L"Resource/Mesh/character/bush/bush.x");

	// 몬스터
	LoadDynamicMeshAsync(L"Resource/Mesh/character/scuttleracer/scuttleracer.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_blue/sru_blue.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_gromp/sru_gromp.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_krug/sru_krug.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_krugmini/sru_krugmini.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_murkwolf/sru_murkwolf.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_murkwolfmini/sru_murkwolfmini_left.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_murkwolfmini/sru_murkwolfmini_right.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_razorbeak/sru_razorbeak.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_razorbeakmini/sru_razorbeakmini.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_red/sru_red.x");

	// 챔피언
	LoadDynamicMeshAsync(L"Resource/Mesh/character/blitzcrank/blitzcrank.X");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/darius/darius.X");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/diana/diana.X");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/garen/garen.X");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/leesin/leesin.X");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/missfortune/missfortune.X");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/leona/leona.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/ahri/ahri.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/jax/jax.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/jinx/jinx.x");

	// 미니언
	LoadDynamicMeshAsync(L"Resource/Mesh/character/order_minion_caster/order_minion_caster.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/order_minion_melee/order_minion_melee.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/order_minion_siege/order_minion_siege.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/order_minion_super/order_minion_super.x");

	LoadDynamicMeshAsync(L"Resource/Mesh/character/chaos_minion_caster/chaos_minion_caster.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/chaos_minion_melee/chaos_minion_melee.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/chaos_minion_siege/chaos_minion_siege.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/character/chaos_minion_super/chaos_minion_super.x");

	// 터렛
	LoadStaticMeshAsync(L"Resource/Mesh/turret_order/turret_order.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/turret_order/sruap_orderturret1_break1.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/turret_order/sruap_orderturret1_break2.x");
	LoadDynamicMeshAsync(L"Resource/Mesh/turret_order/sruap_orderturret1_break3.x");

	// 억제기
	LoadStaticMeshAsync(L"Resource/Mesh/character/order_inhibitor/sruap_orderinhibitor.x");
	// 넥서스
	LoadStaticMeshAsync(L"Resource/Mesh/character/ordernexus/sruap_ordernexus.x");

	// 이펙트
	LoadCustomMeshAsync(L"Resource/Mesh/character/garen/garen_base_q_impact.obj");
	LoadCustomMeshAsync(L"Resource/Mesh/character/garen/garen_base_q_jump.obj");
	LoadCustomMeshAsync(L"Resource/Mesh/character/garen/garen_base_q_sidewall.obj");
	LoadCustomMeshAsync(L"Resource/Mesh/character/garen/garen_base_q_sword_scroll.obj");
	LoadCustomMeshAsync(L"Resource/Mesh/character/garen/garen_base_w_shield.obj");
	LoadCustomMeshAsync(L"Resource/Mesh/character/garen/garen_base_e_spin.obj");
	LoadCustomMeshAsync(L"Resource/Mesh/character/garen/garen_base_r_sword_plane.obj");
	LoadCustomMeshAsync(L"Resource/Mesh/character/garen/garen_base_r_halfdome.obj");


	// 지형
	LoadNavMeshAsync(L"Resource/Mesh/nav/summoner_rift_nav.x");
	LoadStaticMeshAsync(L"Resource/Mesh/nav/nav_wall.x");
	LoadTerrainMeshAsync(L"Resource/Mesh/summoner_rift/summoner_rift.x");

	//지향씨를 위한 디렉토리 순회 예제
	std::filesystem::recursive_directory_iterator dit{ "Resource/UI/"};
	for (auto const& it : dit)
	{
		if (std::filesystem::is_regular_file(it))
		{
			std::cout << it << '\n';
		}
	}
	
}

void TestLoadingScene::LoadStaticMeshAsync(const wstring& filePath)
{
	resourceMax++;
	LoadManager::LoadStaticMeshAsync(filePath, Count);
	
}

void TestLoadingScene::LoadDynamicMeshAsync(const wstring& filePath)
{
	resourceMax++;
	LoadManager::LoadDynamicMeshAsync(filePath, Count);
}

void TestLoadingScene::LoadNavMeshAsync(const wstring& filePath)
{
	resourceMax++;
	LoadManager::LoadNavMeshAsync(filePath, Count);
}

void TestLoadingScene::LoadTerrainMeshAsync(const wstring& filePath)
{
	resourceMax++;
	LoadManager::LoadTerrainMeshAsync(filePath, Count);
}

void TestLoadingScene::LoadCustomMeshAsync(const wstring& filePath)
{
	resourceMax++;
	LoadManager::LoadCustomMeshAsync(filePath, Count);
}

void TestLoadingScene::Count()
{
	_InterlockedIncrement(&resourceLoadCnt);
}

void TestLoadingScene::CreateChampPanel(int borderW, int borderH, int padding)
{
	float ratioX = (float)borderW / 308;
	float ratioY = (float)borderH / 560;

	int spellW = (int)(30 * ratioX);
	int spellH = (int)(30 * ratioY);
	int spell1offsetX = (int)(25 * ratioX);
	int spell2offsetX = (int)(64 * ratioX);
	int spelloffsetY = (int)(488 * ratioY);
	int nameOffsetX = (int)(153 * ratioX);
	int champNameOffsetY = (int)(430 * ratioY);
	int nickNameOffsetY = (int)(525 * ratioY);
	int progressOffsetX = (int)(227 * ratioX);
	int progressOffsetY = (int)(510 * ratioY);

	int borderX = borderW;
	int borderY = padding;
	wstring texKey = L"loadingFrameBlue";

	for (int i = 0; i < 10; i++)
	{
		if (i == 5)
		{
			borderX = borderW;
			borderY = padding * 3 + borderH;
			texKey = L"loadingFrameRed";
		}

		screens[i]->border->SetTexture(texKey);
		screens[i]->border->SetSize(borderW, borderH);
		screens[i]->border->SetLocation(borderX, borderY);
		screens[i]->champ->SetTexture(L"Empty");
		screens[i]->champ->SetSize(borderW, borderH);
		screens[i]->champ->SetLocation(borderX, borderY);
		screens[i]->mask->SetSize(borderW, borderH);
		screens[i]->mask->SetLocation(borderX, borderY);
		screens[i]->spell1->SetTexture(L"Empty");
		screens[i]->spell1->SetSize(spellW, spellH);
		screens[i]->spell1->SetLocation(borderX + spell1offsetX, borderY + spelloffsetY);
		screens[i]->spell2->SetTexture(L"Empty");
		screens[i]->spell2->SetSize(spellW, spellH);
		screens[i]->spell2->SetLocation(borderX + spell2offsetX, borderY + spelloffsetY);
		screens[i]->champName->SetText(L"");
		screens[i]->champName->transform->position = { float(borderX + nameOffsetX), float(borderY + champNameOffsetY),0.f };
		screens[i]->champName->align = Label::Align::Center;
		screens[i]->nickName->SetText(L"");
		screens[i]->nickName->transform->position = { float(borderX + nameOffsetX), float(borderY + nickNameOffsetY),0.f };
		screens[i]->nickName->align = Label::Align::Center;
		screens[i]->progressLabel->SetText(L"0%%");
		screens[i]->progressLabel->transform->position = { float(borderX + progressOffsetX), float(borderY + progressOffsetY),0.f };
		screens[i]->progressLabel->align = Label::Align::Left;
		borderX = borderX + borderW + padding;
		//screens[i]->visible = false;
	}
	
}
