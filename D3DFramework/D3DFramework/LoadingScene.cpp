#include "stdafx.h"
#include "LoadingScene.h"
#include "Label.h"
#include "TestScene.h"
#include "LoadingBackGround.h"
#include "LoadingBorder.h"
#include "LoadingPanel.h"
#include "UI_Spell.h"
#include "LoadingChampPanel.h"
#include "LoadingChampScreen.h"
#include "Label.h"
#include "GameScene.h"

long loadMax = 39;
long loadCount = 0;


void LoadingScene::OnLoaded()
{
	net = Network::GetInstance();
	//ReqEnterGame();

	int screenW = MainGame::GetWidth();
	int screenH = MainGame::GetHeight();

	int borderW = screenW / 8;
	int padding = borderW / 4;
	int borderH = (screenH - borderW) / 2;

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

	SceneManager::GetCurrentScene()->CreateObject<LoadingBackGround>(Layer::UI);
	
	CreateChampPanel(borderW, borderH, padding);

	
}

void LoadingScene::OnUnloaded()
{
}

void LoadingScene::Update()
{
	Scene::Update();
	Network* net = Network::GetInstance();
	float dt = Time::DeltaTime();

	connectTick += dt;

	// 연결 안되어있으면 재연결
	if (isConnected == false)
	{
		// 최종적으로 연결된 상태면 지나감
		if (net->isConnected == false)
		{
			isConnected = true;
			//Network::Connect();
		}
	}
	
	if (net->isConnected)
	{
		NetProc();

		// 접속 패킷보내기 (연결이 보장되어있는 상황)
		if (isEnterGame == false)
		{
			isEnterGame = true;
			ReqEnterGame();
			//ReqTest();
		}

		int per = (int)(((float)loadCount / loadMax) * 100);
		if (loadPercent != per)
		{
			loadPercent = per;
			ReqLoading(loadPercent);
		}

		if (loadCount == loadMax)
		{
			if (isCompleteLoading == false)
			{
				isCompleteLoading = true;
				ReqCompleteLoading();

			}

			//SceneManager::LoadScene<TestScene>();
		}
	}
	

	// 일정 시간 재연결 유도
	if (connectTick > connectDelay)
	{
		connectTick = 0.f;
		isConnected = false;
	}
}

void LoadingScene::LoadResources()
{
	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/character/malphite/malp.X", Count);

	// 오브젝트
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/bush/bush.x", Count);

	// 몬스터
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/scuttleracer/scuttleracer.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_blue/sru_blue.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_gromp/sru_gromp.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_krug/sru_krug.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_krugmini/sru_krugmini.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_murkwolf/sru_murkwolf.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_murkwolfmini/sru_murkwolfmini_left.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_murkwolfmini/sru_murkwolfmini_right.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_razorbeak/sru_razorbeak.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_razorbeakmini/sru_razorbeakmini.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/sru_red/sru_red.x", Count);

	// 챔피언
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/blitzcrank/blitzcrank.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/darius/darius.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/diana/diana.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/garen/garen.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/leesin/leesin.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/missfortune/missfortune.X", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/leona/leona.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/ahri/ahri.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/jax/jax.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/jinx/jinx.x", Count);

	// 미니언
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/order_minion_caster/order_minion_caster.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/order_minion_melee/order_minion_melee.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/order_minion_siege/order_minion_siege.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/order_minion_super/order_minion_super.x", Count);

	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/chaos_minion_caster/chaos_minion_caster.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/chaos_minion_melee/chaos_minion_melee.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/chaos_minion_siege/chaos_minion_siege.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/character/chaos_minion_super/chaos_minion_super.x", Count);


	// 터렛
	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/turret_order/turret_order.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/turret_order/sruap_orderturret1_break1.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/turret_order/sruap_orderturret1_break2.x", Count);
	LoadManager::LoadDynamicMeshAsync(L"Resource/Mesh/turret_order/sruap_orderturret1_break3.x", Count);

	// 넥서스
	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/character/ordernexus/sruap_ordernexus.x", Count);

	LoadManager::LoadNavMeshAsync(L"Resource/Mesh/nav/summoner_rift_nav.x", Count);
	LoadManager::LoadStaticMeshAsync(L"Resource/Mesh/nav/nav_wall.x", Count);
	LoadManager::LoadTerrainMeshAsync(L"Resource/Mesh/summoner_rift/summoner_rift.x", Count);
}

void LoadingScene::Count()
{
	_InterlockedIncrement(&loadCount);
}

void LoadingScene::NetProc()
{
	
	while (net->packQ.size() > 0)
	{
		CPacket* pack = net->packQ.front();
		net->packQ.pop();

		PacketProc(pack);
		delete pack;
	}
}

void LoadingScene::PacketProc(CPacket* pPacket)
{
	WORD type;
	*pPacket >> type;
	switch (type)
	{
	case TEST_RES:
		ResTest(pPacket);
		break;
	case GAME_RES_ENTER_GAME:
		ResEnterGame(pPacket);
		break;
	case GAME_RES_LOADING:
		ResLoading(pPacket);
		break;
	case GAME_RES_COMPLETE_LOADING:
		ResCompleteLoading(pPacket);
		break;

	default:
		Debug::Print("[Warning] 정의되지 않은 패킷 타입 감지\n");
		break;
	}
}

void LoadingScene::ReqTest()
{
	CPacket* pack = new CPacket();
	pack->Clear();
	*pack << (WORD)TEST_REQ;

	Network::SendPacket(pack);
	delete pack;
}

void LoadingScene::ResTest(CPacket* pack)
{
	SceneManager::LoadScene<TestScene>();
}

void LoadingScene::ReqEnterGame()
{
	printf("[INFO] ReqEnterGame 요청\n");
	CPacket* pack = new CPacket();
	pack->Clear();
	*pack << (WORD)GAME_REQ_ENTER_GAME;
	pack->Enqueue((char*)Network::GetInstance()->nick.c_str(), 40);

	Network::SendPacket(pack);
	delete pack;
}

void LoadingScene::ResEnterGame(CPacket* pack)
{
	net->isMultiGame = true;

	int userCount;
	WCHAR nick[20] = {};
	int number;
	BYTE champ, spell1, spell2;
	ChampionType champType;
	SpellType spell1Type, spell2Type;

	*pack >> userCount;

	for (int i = 0; i < userCount; i++)
	{
		pack->Dequeue((char*)nick, 40);
		*pack >> number >> champ >> spell1 >> spell2;

		screens[number]->nickName->text = nick;
		if (screens[number]->nickName->text == net->nick)
		{
			net->users[number].isMine = true;
			net->number = number;
		}
		
		champType = (ChampionType)champ;
		spell1Type = (SpellType)spell1;
		spell2Type = (SpellType)spell2;

		screens[number]->SetChampion(champType);
		screens[number]->SetSpell1(spell1Type);
		screens[number]->SetSpell2(spell2Type);

		net->users[number].number = number;
		net->users[number].champ = champ;
		net->users[number].spell1 = spell1;
		net->users[number].spell2 = spell2;
		net->users[number].nickname = nick;
	}

	LoadResources();
}

void LoadingScene::ReqLoading(int percent)
{
	printf("[INFO] ResEnterGame 요청\n");
	CPacket* pack = new CPacket();
	pack->Clear();
	*pack << (WORD)GAME_REQ_LOADING << percent;

	Network::SendPacket(pack);
	delete pack;
}

void LoadingScene::ResLoading(CPacket* pack)
{
	int userNumber;
	int percent;

	*pack >> userNumber >> percent;

	WCHAR wstr[16] = {};
	swprintf_s(wstr, L"%d%%", percent);
	screens[userNumber]->progressLabel->text = wstr;
}

void LoadingScene::ReqCompleteLoading()
{
	CPacket* pack = new CPacket();
	pack->Clear();
	*pack << (WORD)GAME_REQ_COMPLETE_LOADING;
	
	Network::SendPacket(pack);
	delete pack;
}

void LoadingScene::ResCompleteLoading(CPacket* pack)
{
	printf("로딩 완료\n");
	SceneManager::LoadScene<GameScene>();
}

void LoadingScene::CreateChampPanel(int borderW, int borderH, int padding)
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

		screens[i] = (LoadingChampScreen*)SceneManager::GetCurrentScene()->CreateObject<LoadingChampScreen>(Layer::UI);
		screens[i]->border->SetSize(borderW, borderH);
		screens[i]->border->SetLocation(borderX, borderY);
		screens[i]->border->SetTexture(texKey);
		screens[i]->champ->SetSize(borderW, borderH);
		screens[i]->champ->SetLocation(borderX, borderY);
		screens[i]->champ->SetTexture(L"Empty");
		screens[i]->mask->SetSize(borderW, borderH);
		screens[i]->mask->SetLocation(borderX, borderY);
		screens[i]->spell1->SetSize(spellW, spellH);
		screens[i]->spell1->SetLocation(borderX + spell1offsetX, borderY + spelloffsetY);
		screens[i]->spell1->SetTexture(L"Empty");
		screens[i]->spell2->SetSize(spellW, spellH);
		screens[i]->spell2->SetLocation(borderX + spell2offsetX, borderY + spelloffsetY);
		screens[i]->spell2->SetTexture(L"Empty");
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
	}
}
