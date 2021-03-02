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

#include "PlayerInfoPanel.h" // TODO : 테스트 끝나면 빼기

long resourceMax = 39;
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

#if 0 // TODO : 임시 코드니까 다되면 꼭 빼야됨
	UIManager::GetInstance()->AddUI(PlayerInfoPanel::GetInstance());
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
	WCHAR buf[16] = {};
	swprintf_s(buf, L"%d%%", loadPercent);
	screens[0]->progressLabel->text = buf;

	if (resourceLoadCnt == resourceMax)
	{
		SceneManager::LoadScene<TestScene>();
	}
}

void TestLoadingScene::LoadResources()
{
	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/character/malphite/", L"malp.X", Count);
	
	// 오브젝트
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/bush/", L"bush.x", Count);

	// 몬스터
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/scuttleracer/", L"scuttleracer.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_blue/", L"sru_blue.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_gromp/", L"sru_gromp.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_krug/", L"sru_krug.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_krugmini/", L"sru_krugmini.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_murkwolf/", L"sru_murkwolf.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_murkwolfmini/", L"sru_murkwolfmini_left.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_murkwolfmini/", L"sru_murkwolfmini_right.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_razorbeak/", L"sru_razorbeak.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_razorbeakmini/", L"sru_razorbeakmini.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_red/", L"sru_red.x", Count);

	// 챔피언
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/blitzcrank/", L"blitzcrank.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/darius/", L"darius.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/diana/", L"diana.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/garen/", L"garen.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/leesin/", L"leesin.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/missfortune/", L"missfortune.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/leona/", L"leona.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/ahri/", L"ahri.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/jax/", L"jax.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/jinx/", L"jinx.x", Count);

	// 미니언
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/order_minion_caster/", L"order_minion_caster.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/order_minion_melee/", L"order_minion_melee.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/order_minion_siege/", L"order_minion_siege.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/order_minion_super/", L"order_minion_super.x", Count);

	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/chaos_minion_caster/", L"chaos_minion_caster.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/chaos_minion_melee/", L"chaos_minion_melee.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/chaos_minion_siege/", L"chaos_minion_siege.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/chaos_minion_super/", L"chaos_minion_super.x", Count);

	// 터렛
	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/turret_order/", L"turret_order.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/turret_order/", L"sruap_orderturret1_break1.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/turret_order/", L"sruap_orderturret1_break2.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/turret_order/", L"sruap_orderturret1_break3.x", Count);

	// 넥서스
	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/character/ordernexus/", L"sruap_ordernexus.x", Count);

	LoadManager::LoadNavMeshAsync(L"Resource/Mesh/nav/", L"summoner_rift_nav.x", Count);
	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/nav/", L"nav_wall.x", Count);
	LoadManager::LoadTerrainMeshAsync(L"Resource/Mesh/summoner_rift/", L"summoner_rift.x", Count);


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
		screens[i]->champName->text = L"";
		screens[i]->champName->transform->position = { float(borderX + nameOffsetX), float(borderY + champNameOffsetY),0.f };
		screens[i]->champName->align = Label::Align::Center;
		screens[i]->nickName->text = L"";
		screens[i]->nickName->transform->position = { float(borderX + nameOffsetX), float(borderY + nickNameOffsetY),0.f };
		screens[i]->nickName->align = Label::Align::Center;
		screens[i]->progressLabel->text = L"0%";
		screens[i]->progressLabel->transform->position = { float(borderX + progressOffsetX), float(borderY + progressOffsetY),0.f };
		screens[i]->progressLabel->align = Label::Align::Left;
		borderX = borderX + borderW + padding;
		//screens[i]->isVisible = false;
	}
	
}
