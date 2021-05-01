#include "stdafx.h"
#include "TestScene.h"

#include "UIManager.h"
#include "Label.h"
#include "MinimapPanel.h"
#include "PlayerInfoPanel.h"
#include "FloatingBar.h"
#include "MiniScorePanel.h"
#include "ItemshopPanel.h"
#include "ScorePanel.h"
#include "EndofgamePanel.h"
#include "AnnouncerPanel.h"
#include "KillCalloutPanel.h"

#include "SkyBox.h"
#include "Environment.h"
#include "TestMan.h"
#include "PlayerController.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "NavMeshMap.h"
#include "TestGaren.h"
#include "Wall.h"
#include "Turret.h"
#include "Bush.h"
#include "BushGroup.h"

#include "Inhibitor.h"
#include "AllChampion.h"
#include "AllMinion.h"
#include "AllMonster.h"

#include "MonsterAI.h"

#include "Nexus.h"
#include "MinionAI.h"

#include "RenderSystem.h"

#include "MinionSpawner.h"

#include "ChampionAI.h"

#include "DistortionRenderer.h"
#include "EffectObject.h"
#include "Effect_Trail.h"

void TestScene::OnLoaded()
{
	MinionSpawner::GetInstance();

	Camera::GetInstance()->SetPosition(Vector3(0.f, 1.f ,-1.f));
	Camera::GetInstance()->transform->look = Vector3(0, 0, 1);

	testLabel = (Label*)SceneManager::GetCurrentScene()->CreateObject<Label>(Layer::UI);
	testLabel->SetText(L"TestScene");
	testLabel->SetColor(255, 0, 255, 0);

	CreateEnvironment();
	CreateBuilding();
	CreateMonster();

	// 플레이어
	Unit* unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Garen>(Layer::Unit);
	unitMap[0] = unit;
	unit->transform->position = { 41.f, 68.48f, 46.f };
	//unit->transform->position = { 15.68f, 66.91f, -11.16f };
	unit->SetSpawnPosition(Vector3(41.f, 68.48f, 46.f));
	unit->SetTeam(Team::BLUE);
	unit->AddComponent<PlayerController>(L"PlayerController");
	Camera::GetInstance()->SetTarget(unit);
	Champion* champ = (Champion*)unit;
	champ->SetNickname(L"테스트닉네임");
	champ->SetID((UINT)0);
	//champ->AddItem(3742);

	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Missfortune>(Layer::Unit);
	unitMap[5] = unit;
	unit->transform->position = { -47.48f,68.48f,-41.34f };
	unit->SetSpawnPosition(unit->transform->position);
	unit->SetTeam(Team::RED);
	unit->AddComponent<ChampionAI>(L"AI");
	Champion* champ2 = (Champion*)unit;
	champ2->SetNickname(L"미스포츈");
	champ2->SetID((UINT)5);

	//trail = (Effect_Trail*)SceneManager::GetCurrentScene()->CreateObject<Effect_Trail>(Layer::Effect);
	//trail->transform->position = { 36.f,69.f,46.f };
	//trailPos = trail->transform->position;

	D3DLIGHT9 dirLight{};
	Vector3 v = Vector3(-2, -4.f, 0.5f).Normalized();
	dirLight.Type = D3DLIGHT_DIRECTIONAL;
	dirLight.Direction = v;
	dirLight.Diffuse = D3DCOLORVALUE{ 1.f, 1.f, 1.f, 1.f };
	dirLight.Ambient = D3DCOLORVALUE{ 0.7f, 0.7f, 0.7f, 1.0f};
	Engine::RenderSystem::AddLight(L"dir1", dirLight);
	Engine::RenderSystem::EnableShadow(L"dir1");

	// UI 생성 및 추가
	UIManager::GetInstance()->AddUI(PlayerInfoPanel::GetInstance());
	UIManager::GetInstance()->AddUI(MinimapPanel::GetInstance());
	UIManager::GetInstance()->AddUI(MiniScorePanel::GetInstance());
	UIManager::GetInstance()->AddUI(ItemshopPanel::GetInstance());
	UIManager::GetInstance()->AddUI(ScorePanel::GetInstance());
	UIManager::GetInstance()->AddUI(EndofgamePanel::GetInstance());
	UIManager::GetInstance()->AddUI(AnnouncerPanel::GetInstance());
	UIManager::GetInstance()->AddUI(KillCalloutPanel::GetInstance());

	ItemshopPanel::GetInstance()->Hide();
	ScorePanel::GetInstance()->Hide();

	PlayerInfoPanel::GetInstance()->SetTarget(champ);
	ItemshopPanel::GetInstance()->SetTarget(champ);
	ScorePanel::GetInstance()->AddChampion(champ, true);
	ScorePanel::GetInstance()->AddChampion(champ2);
	MinimapPanel::GetInstance()->AddChampion(champ);
	MinimapPanel::GetInstance()->AddChampion(champ2);

	EndofgamePanel::GetInstance()->Hide();
	SoundManager::PlayBGM(L"Background1.ogg");
}

void TestScene::OnUnloaded()
{
	MinionSpawner::Destroy();
	BushGroup::Destroy();
}

void TestScene::Update()
{
	float dt = Time::DeltaTime();
	Scene::Update();

	Stat* playerStat = unitMap[0]->stat;
	MiniScorePanel::GetInstance()->SetMinionScore((int)playerStat->GetBaseValue(StatType::MinionKilled));
	MiniScorePanel::GetInstance()->SetKillScore((int)playerStat->GetBaseValue(StatType::KillScore));
	MiniScorePanel::GetInstance()->SetDeathScore((int)playerStat->GetBaseValue(StatType::DeathScore));
	MiniScorePanel::GetInstance()->SetAssistScore((int)playerStat->GetBaseValue(StatType::AssistScore));

	Progress();
}

void TestScene::PostUpdate()
{
	Scene::PostUpdate();

	MinionSpawner::Update();
}

void TestScene::Progress()
{
	int minute = 0;
	int second = 0;
	MiniScorePanel::GetInstance()->GetTime(&minute, &second);

	if (minute == 0 && second == 25)
	{
		static bool play = false;
		if (!play) {
			AnnouncerPanel::GetInstance()->AddAnnouncer(L"소환사의 협곡에 오신 것을 환영합니다", Team::BLUE, L"소환사의협곡에오신것을환영합니다.wav");
			play = true;
		}
	}
	else if (minute == 0 && second == 35)
	{
		static bool play = false;
		if (!play) {
			AnnouncerPanel::GetInstance()->AddAnnouncer(L"미니언 생성까지 30초 남았습니다", Team::BLUE, L"미니언생성까지30초남았습니다.wav");
			play = true;
		}
	}
	else if (minute == 1 && second == 5)
	{
		static bool play = false;
		if (!play) {
			AnnouncerPanel::GetInstance()->AddAnnouncer(L"미니언이 생성되었습니다", Team::BLUE, L"미니언이생성되었습니다.wav");
			MinionSpawner::Spawn();
			play = true;
		}
	}
}

//============================================================================================
void TestScene::CreateEnvironment()
{
	GameObject* obj = nullptr;
	// 오브젝트
	obj = SceneManager::GetCurrentScene()->CreateObject<Environment>();
	obj->transform->position = { 0,0,0 };

	// 바닥
	obj = SceneManager::GetCurrentScene()->CreateObject<NavMeshMap>(Layer::Ground);

	// 벽
	obj = SceneManager::GetCurrentScene()->CreateObject<Wall>(Layer::Wall);

	// 부쉬
	Bush* bush = nullptr;
	BushGroup* bushGroup = nullptr;


	////////////////////////// 1
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 8.9f,67.71f,29.69f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 8.87f,67.71f,28.96f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 8.67f,67.71f,28.5f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 8.02f,67.71f,28.51f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 6.85f,67.71f,28.28f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 7.52f,67.71f,28.27f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 7.4f,67.71f,27.78f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 8.19f,67.71f,27.94f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 2
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 1.71f,67.71f,30.55f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 1.11f,67.71f,30.80f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 0.46f,67.71f,30.96f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -0.11f,67.71f,31.f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -0.71f,67.71f,30.89f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -1.32f,67.71f,30.78f };
	bushGroup->bushList.push_back(bush);
	////////////////////////// 3 아랫작골부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -13.98f,67.71f,37.44f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -14.63f,67.71f,37.28f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -15.27f,67.71f,37.18f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -15.86f,67.71f,37.03f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -16.39f,67.71f,36.86f };
	bushGroup->bushList.push_back(bush);
	////////////////////////// 4 봇삼거리
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -21.66,67.71f,32.04f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -22.21f,67.71f,31.53f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -22.71f,67.68f,31.22f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -23.36f,67.65f,31.05f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -24.02f,67.62f,31.06f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -22.48f,67.69f,30.62f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -22.26f,67.7f,29.96f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -23.01f,67.67f,30.34f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -21.84f,67.72f,30.98f };
	bushGroup->bushList.push_back(bush);
	////////////////////////// 5 아랫레드부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -6.39f,67.71f,28.09f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -6.87f,67.71f,28.37f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -7.52f,67.71f,28.49f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -8.32f,67.71f,28.42f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -8.88f,67.71f,28.21f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -9.5f,67.71f,27.97f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 6 아랫레드 뒤쪽부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -11.52f,67.71f,21.84f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -11.35f,67.71f,21.4f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -11.08f,67.71f,20.81f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -10.88f,67.71f,20.29f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -10.57f,67.71f,19.99f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -10.15f,67.71f,20.13f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 7 아랫칼부 부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 1.31f,67.71f,20.f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 1.42f,67.71f,20.7f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 1.5f,67.71f,21.43f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 2.19f,67.71f,21.52f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 2.06f,67.71f,20.84f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 1.99f,67.71f,19.99f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 8 왼쪽늑대 뒤쪽부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 12.51f,67.71f,6.16f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 12.57f,67.71f,5.55f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 12.8f,67.71f,4.9f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 13.13f,67.71f,4.29f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 13.86f,67.71f,4.47f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 13.43f,67.71f,5.08f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 13.01f,67.71f,5.7f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 9 왼쪽블루 부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 21.33f,67.71f,1.26f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 21.96f,67.71f,1.31f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 22.68f,67.71f,1.42f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 22.75f,67.71f,0.89f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 22.11f,67.71f,0.75f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 21.51f,67.71f,0.67f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 10 왼쪽두꺼비 윗쪽부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 29.56f,67.71f,-10.14f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 29.45f,67.71f,-10.72f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 29.43f,67.71f,-11.25f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 29.4f,67.71f,-11.92f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 29.41f,67.71f,-12.66f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 28.68f,67.71f,-10.99f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 28.6f,67.71f,-11.74f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 27.87f,67.71f,-11.43f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 11 블루 뒷쪽강가부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 12.17f,67.53f,-2.89f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 11.63f,67.33f,-3.34f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 11.09f,67.14f,-3.67f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 10.63f,67.01f,-3.87f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 10.06f,67.f,-3.96f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 12 윗쪽 미드일자강가부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 4.04f,66.91f,-1.12f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 3.38f,66.91f,-1.45f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 2.75f,66.91f,-1.92f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 2.1f,66.91f,-2.51f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 1.45f,66.91f,-3.02f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 0.85f,66.91f,-3.41f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 0.24f,66.91f,-3.77f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 13 윗쪽 강가 한칸부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 9.64f,66.91f,-8.03f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 9.94f,66.95f,-7.35f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 10.82f,66.92f,-7.66f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 10.57f,66.91f,-8.4f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 14 윗쪽 탑 강가부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 25.63f,66.91f,-21.88f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 24.96f,66.95f,-20.81f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 24.47f,66.92f,-19.84f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 24.12f,66.91f,-18.95f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 23.66f,66.91f,-19.44f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 23.97f,66.91f,-20.23f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 24.37f,66.91f,-21.21f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 24.91f,66.91f,-22.28f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 15 윗쪽 탑 삼거리부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 16.39f,67.65f,-25.1f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 15.52f,67.67f,-25.35f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 14.83f,67.69f,-25.62f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 14.15f,67.61f,-25.96f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 15.8f,67.64f,-24.28f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 14.7f,67.68f,-24.43f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 15.07f,67.64f,-23.21f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 15.16f,67.64f,-24.22f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 16 윗작골 부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 8.94f,67.71f,-30.1f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 8.17f,67.71f,-30.32f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 7.35f,67.71f,-30.55f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 6.56f,67.71f,-30.74f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 5.8f,67.71f,-30.83f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 17 위에 긴 일자부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -5.61f,67.71f,-24.53f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -6.32f,67.71f,-24.76f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -7.09f,67.71f,-24.85f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -7.68f,67.71f,-24.79f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -8.51f,67.71f,-24.53f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 18
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -16.12f,67.71f,-23.17f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -16.06f,67.71f,-22.35f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -15.36f,67.71f,-22.1f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -14.68f,67.71f,-22.02f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -14.01f,67.71f,-22.f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 19 윗레드 부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -1.11f,67.71f,-21.53f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -0.76f,67.71f,-22.01f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -0.03f,67.71f,-22.26f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 0.65f,67.71f,-22.32f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 1.41f,67.71f,-22.05f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 1.99f,67.71f,-21.65f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 20 윗레드 뒤쪽부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 4.04f,67.71f,-15.99f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 4.02f,67.71f,-15.38f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 3.96f,67.71f,-14.83f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 3.81f,67.71f,-14.31f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 3.5f,67.71f,-13.97f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { 3.07f,67.71f,-13.85f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 21 윗칼부 부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -8.96f,67.71f,-15.5f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -9.66f,67.71f,-15.46f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -8.91f,67.71f,-14.87f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -9.66f,67.71f,-14.75f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -8.77f,67.71f,-14.15f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -9.6f,67.71f,-14.05f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 22 윗늑대 뒷쪽부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -19.73f,67.71f,-0.55f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -19.95f,67.71f,-0.11f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -20.1f,67.71f,0.29f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -20.2f,67.71f,0.69f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -20.26f,67.71f,1.23f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -20.46f,67.71f,-0.18f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -20.56f,67.71f,0.32f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -20.65f,67.71f,0.74f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 23 윗블루 부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -28.8f,67.71f,5.05f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -29.56f,67.71f,5.06f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -30.34f,67.71f,4.97f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -29.14f,67.71f,5.42f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -29.8f,67.71f,5.47f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -30.5f,67.71f,5.47f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 24 윗두꺼비 아랫부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -37.02f,67.71f,16.39f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -36.88f,67.71f,17.02f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -36.76f,67.71f,17.64f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -36.73f,67.71f,18.61f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -35.86f,67.71f,16.84f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -35.76f,67.71f,17.6f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -35.68f,67.71f,18.28f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -35.19f,67.71f,17.78f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 25 윗블루뒷쪽 강가부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -20.07f,67.71f,8.49f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -19.69f,67.63f,8.98f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -19.27f,67.53f,9.33f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -18.77f,67.39f,9.66f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -18.46f,67.27f,10.09f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -18.08f,67.1f,10.34f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 26 미드아래 강가일자부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -11.89f,66.91f,8.f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -11.38f,66.91f,8.39f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -10.84f,66.91f,8.7f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -10.35f,66.91f,9.11f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -9.74f,66.91f,9.51f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -9.34f,66.91f,9.85f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -8.87f,66.91f,10.29f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -8.36f,66.91f,10.89f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -8.14f,66.91f,11.25f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 27 아래강가 한칸부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -15.98f,66.91f,14.34f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -16.68f,66.91f,14.22f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -16.22f,66.91f,14.93f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -16.84f,66.91f,14.8f };
	bushGroup->bushList.push_back(bush);

	////////////////////////// 28 바텀 강가부쉬
	bushGroup = new BushGroup;
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -31.42f,66.91f,24.63f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -32.18f,66.91f,24.45f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -32.36f,66.91f,25.12f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -32.57f,66.91f,25.67f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -32.7f,66.91f,26.3f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -32.84f,66.91f,27.f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -32.09f,66.91f,26.37f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -31.86f,66.91f,25.89f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -31.59f,66.91f,25.48f };
	bushGroup->bushList.push_back(bush);
	bush = (Bush*)SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	bush->transform->position = { -32.29f,66.91f,26.97f };
	bushGroup->bushList.push_back(bush);


	/*obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.98f,67.71f,29.14f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.90f, 67.71f, 29.87f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.84f, 67.71f, 29.55f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.50f, 67.71f, 28.95f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.90f, 67.71f, 28.73f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.70f, 67.71f, 28.37f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.39f, 67.71f, 28.22f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.01f, 67.71f, 28.06f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.71f, 67.71f, 27.92f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.41f, 67.71f, 27.83f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.99f, 67.71f, 28.52f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.54f, 67.71f, 28.44f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.68f, 67.71f, 28.77f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.15f, 67.71f, 28.61f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.00f, 67.71f, 28.84f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 6.83f, 67.71f, 28.54f };
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 6.99f, 67.71f, 28.18f };*/
}

void TestScene::CreateBuilding()
{
	Unit* unit = nullptr;
	int unitID = (int)UnitID::TurretBlueBot1;
	Unit* beforeBuilding = nullptr;
	list<Unit*> inhibitors;
	list<Unit*> twinTurrets;
	// 블루팀 타워


	// bottom1
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -23.15f, 67.71f, 44.17f };
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;
	// bottom2
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -0.30f, 67.71f, 41.20f };
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;
	// bottom3
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 16.41f, 67.87f, 42.5f };
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;

	// inhibitor bot
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Inhibitor>(Layer::Building);
	unit->transform->position = { 21.52f,68.04f,42.62f };
	unit->SetSpawnPosition(Vector3{ 21.52f,68.04f,42.62f });
	unit->transform->eulerAngles.y = D3DXToRadian(180.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	inhibitors.emplace_back(unit);
	unit->SetID(unitID);
	unitID++;

	// mid1
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 6.50f, 67.71f, 10.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;
	// mid2
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 11.61f, 67.71f, 20.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;
	// mid3
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 20.51f, 67.87f, 27.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;

	// inhibitor mid
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Inhibitor>(Layer::Building);
	unit->transform->position = { 23.26f,68.04f,29.98f };
	unit->SetSpawnPosition(Vector3{ 23.26f,68.04f,29.98f });
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	inhibitors.emplace_back(unit);
	unit->SetID(unitID);
	unitID++;

	// top1
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 37.42f, 67.71f, -16.f };
	unit->transform->eulerAngles.y = D3DXToRadian(45.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;
	// top2
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 34.12f, 67.71f, 8.f };
	unit->transform->eulerAngles.y = D3DXToRadian(45.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;

	// top3
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 36.36f, 67.87f, 23.f };
	unit->transform->eulerAngles.y = D3DXToRadian(45.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;

	// inhibitor top
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Inhibitor>(Layer::Building);
	unit->transform->position = { 36.23f,68.04f,27.62f };
	unit->SetSpawnPosition(Vector3{ 36.23f,68.04f,27.62f });
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	inhibitors.emplace_back(unit);
	unit->SetID(unitID);
	unitID++;


	// twin Left
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 32.35f, 68.f, 36.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	for(auto& _unit : inhibitors)
		dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)_unit);
	twinTurrets.emplace_back(unit);
	unit->SetID(unitID);
	unitID++;
	// twin Right
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 29.46f, 68.f, 39.3f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	for (auto& _unit : inhibitors)
		dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)_unit);
	twinTurrets.emplace_back(unit);
	unit->SetID(unitID);
	unitID++;

	// nexus
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Nexus>(Layer::Building);
	unit->transform->position = { 33.83f,68.04f,40.00f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	for (auto& _unit : twinTurrets)
		dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)_unit);
	unit->SetID(unitID);
	unitID++;

	// 퍼플팀
	inhibitors.clear();
	twinTurrets.clear();
	// bottom1
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -44.71f,67.71f,21.98f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;
	// bottom2
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -41.30f,67.71f,-1.89f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;
	// bottom3
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -43.20f,68.f,-16.83f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;

	// inhibitor bot
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Inhibitor>(Layer::Building);
	unit->transform->position = { -43.17f,68.04f,-21.56f };
	unit->SetSpawnPosition(Vector3{ -43.17f,68.04f,-21.56f });
	unit->transform->eulerAngles.y = D3DXToRadian(0.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	inhibitors.emplace_back(unit);
	unit->SetID(unitID);
	unitID++;

	// mid1
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -13.30f,67.71f,-3.61f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;

	// mid2
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -18.52f,67.71f,-13.85f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;

	// mid3
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -27.21f,68.f,-20.97f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;

	// inhibitor mid
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Inhibitor>(Layer::Building);
	unit->transform->position = { -30.25f,68.04f,-23.81f };
	unit->SetSpawnPosition(Vector3{ -30.25f,68.04f,-23.81f });
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	inhibitors.emplace_back(unit);
	unit->SetID(unitID);
	unitID++;


	// top1
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 16.28f,67.71f,-37.99f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;
	// top2
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -6.93f,67.71f,-34.96f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;
	// top3
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -23.09f,68.f,-36.63f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	beforeBuilding = unit;
	unit->SetID(unitID);
	unitID++;

	// inhibitor top
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Inhibitor>(Layer::Building);
	unit->transform->position = { -28.04f,68.04f,-36.64f };
	unit->SetSpawnPosition(Vector3{ -28.04f,68.04f,-36.64f });
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)beforeBuilding);
	inhibitors.emplace_back(unit);
	unit->SetID(unitID);
	unitID++;

	// twin left
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -39.52f,68.00f,-29.97f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	for (auto& _unit : inhibitors)
		dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)_unit);
	twinTurrets.emplace_back(unit);
	unit->SetID(unitID);
	unitID++;
	// twin right
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -36.64f,68.00f,-32.90f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	for (auto& _unit : inhibitors)
		dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)_unit);
	twinTurrets.emplace_back(unit);
	unit->SetID(unitID);
	unitID++;


	// nexus
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Nexus>(Layer::Building);
	unit->transform->position = { -40.75f,68.04f,-33.86f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	for (auto& _unit : twinTurrets)
		dynamic_cast<Building*>(unit)->frontBuildingList.emplace_back((Building*)_unit);
	unit->SetID(unitID);
	unitID++;
}

void TestScene::CreateMonster()
{
	Unit* unit = nullptr;
	int unitID = (int)UnitID::Red1;
	// 몬스터

	// 레드
	unit = (Unit*)(Unit*)SceneManager::GetCurrentScene()->CreateObject<RedMonster>(Layer::Unit);
	unit->transform->position = { -6.10f, 67.71f, 24.87f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<RedMonster>(Layer::Unit);
	unit->transform->position = { -1.88f, 67.71f, -17.87f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// 블루
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<BlueMonster>(Layer::Unit);
	unit->transform->position = { 19.79f, 67.72f, 0.64f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<BlueMonster>(Layer::Unit);
	unit->transform->position = { -26.43f, 67.71f, 6.83f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// 늑대 위
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Murkwolf>(Layer::Unit);
	unit->transform->position = { 19.74f, 67.71f, 9.78f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<MurkwolfMini>(Layer::Unit);
	unit->transform->position = { 19.17f, 67.71f, 10.84f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<MurkwolfMini>(Layer::Unit);
	unit->transform->position = { 21.08f, 67.71f, 9.00f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// 늑대 아래
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Murkwolf>(Layer::Unit);
	unit->transform->position = { -26.72f, 67.72f, -2.72f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<MurkwolfMini>(Layer::Unit);
	unit->transform->position = { -26.23f, 67.71f, -3.57f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<MurkwolfMini>(Layer::Unit);
	unit->transform->position = { -27.73f, 67.71f, -2.44f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// 두꺼비
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Gromp>(Layer::Unit);
	unit->transform->position = { 29.28f, 67.73f, -2.82f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Gromp>(Layer::Unit);
	unit->transform->position = { -36.59f, 67.71f, 10.14f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// 짹짹이 위
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Razorbeak>(Layer::Unit);
	unit->transform->position = { -0.75f, 67.71f, 16.17f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -1.32f, 67.71f, 15.52f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -1.69f, 67.71f, 16.20f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -1.71f, 67.71f, 17.11f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -0.98f, 67.71f, 17.65f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { 0.08f, 67.71f, 17.21f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// 짹짹이 아래
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Razorbeak>(Layer::Unit);
	unit->transform->position = { -6.43f, 67.71f, -10.09f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -5.53f, 67.71f, -9.14f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -5.56f, 67.71f, -10.09f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -5.91f, 67.71f, -11.04f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -6.81f, 67.71f, -10.93f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<RazorbeakMini>(Layer::Unit);
	unit->transform->position = { -7.31f, 67.71f, -10.48f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;


	// 작골
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Krug>(Layer::Unit);
	unit->transform->position = { -10.05f, 67.71f, 33.49f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Krug>(Layer::Unit);
	unit->transform->position = { 3.13f, 67.71f, -26.61f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// 바위게
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Scuttleracer>(Layer::Unit);
	unit->transform->position = { 15.06f, 66.91f, -9.49f };
	unit->SetSpawnPosition(unit->transform->position);
	((Scuttleracer*)unit)->SetAI(Scuttleracer::ScuttlePos::North);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Scuttleracer>(Layer::Unit);
	unit->transform->position = { -24.36f, 66.91f, 17.82f };
	unit->SetSpawnPosition(unit->transform->position);
	((Scuttleracer*)unit)->SetAI(Scuttleracer::ScuttlePos::South);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
}
