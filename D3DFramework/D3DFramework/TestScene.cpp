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


#include "AllChampion.h"
#include "AllMinion.h"
#include "AllMonster.h"

#include "MonsterAI.h"

#include "Nexus.h"
#include "MinionAI.h"

#include "RenderSystem.h"

#include "EffectObject.h"
#include "Skill_Item_Dreadnought.h"

void TestScene::OnLoaded()
{
	Camera::GetInstance()->SetPosition(Vector3(0.f, 1.f ,-1.f));
	Camera::GetInstance()->transform->look = Vector3(0, 0, 1);

	testLabel = (Label*)SceneManager::GetCurrentScene()->CreateObject<Label>(Layer::UI);
	testLabel->SetText(L"123123\n123123");
	testLabel->SetColor(255, 0, 255, 0);

	CreateEnvironment();
	CreateBuilding();
	CreateMonster();

	// 플레이어
	Unit* unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Garen>(Layer::Unit);
	unit->transform->position = { 41.f, 68.f, 46.f };
	unit->SetSpawnPosition(Vector3(41.f, 68.f, 46.f));
	unit->SetTeam(Team::BLUE);
	unit->AddComponent<PlayerController>(L"PlayerController");
	Camera::GetInstance()->SetTarget(unit);
	Champion* champ = (Champion*)unit;
	champ->SetNickname(L"테스트닉네임");
	champ->SetID((UINT)0);
	Item* item = ItemManager::GetInstance()->GetItem(3742);
	champ->AddItem(item);
	Buff_Item* buffItem = item->StatBuffSetting(unit);

	buffItem->AddModifier(StatType::MaxHealth, 400.f);
	buffItem->AddModifier(StatType::Armor, 100.f);
	buffItem->AddModifier(StatType::MovementSpeed, 0.05f, true);
	//
	item = ItemManager::GetInstance()->GetItem(3742);
	champ->AddItem(item);
	buffItem = item->StatBuffSetting(unit);

	buffItem->AddModifier(StatType::MaxHealth, 400.f);

	//
	
	//item->skillList.push_back(new Skill_Item_Dreadnought(unit));

	GameObject* obj = SceneManager::GetCurrentScene()->CreateObject<EffectObject>(Layer::Default);
	obj->transform->position = { 36.f,69.f,46.f };


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

	ItemshopPanel::GetInstance()->Hide();
	ScorePanel::GetInstance()->Hide();

	PlayerInfoPanel::GetInstance()->SetTarget(champ);
	ItemshopPanel::GetInstance()->SetTarget(champ);
	ScorePanel::GetInstance()->AddChampion(champ, true);
}

void TestScene::OnUnloaded()
{
}

void TestScene::Update()
{
	Scene::Update();

	if (testUnit != nullptr)
	{
		if (Input::GetKey(VK_UP))
		{
			testUnit->transform->position.z -= Time::DeltaTime();
			printf("%.2ff,%.2ff,%.2ff\n", testUnit->transform->position.x, testUnit->transform->position.y, testUnit->transform->position.z);

		}
		if (Input::GetKey(VK_DOWN))
		{
			testUnit->transform->position.z += Time::DeltaTime();
			printf("%.2ff,%.2ff,%.2ff\n", testUnit->transform->position.x, testUnit->transform->position.y, testUnit->transform->position.z);

		}
		if (Input::GetKey(VK_LEFT))
		{
			testUnit->transform->position.x += Time::DeltaTime();
			printf("%.2ff,%.2ff,%.2ff\n", testUnit->transform->position.x, testUnit->transform->position.y, testUnit->transform->position.z);

		}
		if (Input::GetKey(VK_RIGHT))
		{
			testUnit->transform->position.x -= Time::DeltaTime();
			printf("%.2ff,%.2ff,%.2ff\n", testUnit->transform->position.x, testUnit->transform->position.y, testUnit->transform->position.z);

		}
	}
	
	if (Input::GetKeyDown('M'))
	{
		CreateMinionCaster();
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
	obj = SceneManager::GetCurrentScene()->CreateObject<Bush>(Layer::Bush);
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
	obj->transform->position = { 6.99f, 67.71f, 28.18f };
}

void TestScene::CreateBuilding()
{
	Unit* unit = nullptr;
	int unitID = (int)UnitID::TurretBlueBot1;


	// 블루팀 타워

	// bottom1
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -23.15f, 67.71f, 44.17f };
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// bottom2
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -0.30f, 67.71f, 41.20f };
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// bottom3
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 16.41f, 67.87f, 42.5f };
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// mid1
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 6.50f, 67.71f, 10.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// mid2
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 11.61f, 67.71f, 20.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// mid3
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 20.51f, 67.87f, 27.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// top1
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 37.42f, 67.71f, -16.f };
	unit->transform->eulerAngles.y = D3DXToRadian(45.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// top2
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 34.12f, 67.71f, 8.f };
	unit->transform->eulerAngles.y = D3DXToRadian(45.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// top3
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 36.36f, 67.87f, 23.f };
	unit->transform->eulerAngles.y = D3DXToRadian(45.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;


	// twin Left
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 32.35f, 68.f, 36.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// twin Right
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 29.46f, 68.f, 39.3f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;


	// 퍼플팀

	// bottom1
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -44.71f,67.71f,21.98f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// bottom2
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -41.30f,67.71f,-1.89f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// bottom3
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -43.20f,68.f,-16.83f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// mid1
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -13.30f,67.71f,-3.61f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// mid2
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -18.52f,67.71f,-13.85f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// mid3
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -27.21f,68.f,-20.97f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;


	// top1
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 16.28f,67.71f,-37.99f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// top2
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -6.93f,67.71f,-34.96f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// top3
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -23.09f,68.f,-36.63f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	// twin left
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -39.52f,68.00f,-29.97f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
	// twin right
	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -36.64f,68.00f,-32.90f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	unitMap[unitID] = unit;
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
	unit->transform->position = { 15.68f, 66.91f, -11.16f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;

	unit = (Unit*)SceneManager::GetCurrentScene()->CreateObject<Scuttleracer>(Layer::Unit);
	unit->transform->position = { -24.36f, 66.91f, 17.82f };
	unit->SetSpawnPosition(unit->transform->position);
	unitMap[unitID] = unit;
	unit->SetID(unitID);
	unitID++;
}

void TestScene::CreateMinionCaster()
{
	Minion* minion = nullptr;

	// 블루
	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionCaster>(Layer::Unit);
	minion->transform->position = { 29.47f,68.04f,41.74f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -30.88f,67.71f,40.80f };
	minion->ai->wayPoint.push_back(Vector3(-42.32f, 67.71f, 28.58f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionCaster>(Layer::Unit);
	minion->transform->position = { 30.64f,68.04f,37.51f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionCaster>(Layer::Unit);
	minion->transform->position = { 35.00f,68.04f,35.55f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { 34.58f,67.71f,-23.79f };
	minion->ai->wayPoint.push_back(Vector3(23.98f, 67.71f, -34.88f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	// 레드
	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionCaster>(Layer::Unit);
	minion->transform->position = { -43.05f,68.01f,-29.62f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -42.32f,67.71f,28.58f };
	minion->ai->wayPoint.push_back(Vector3(-30.88f, 67.71f, 40.80f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionCaster>(Layer::Unit);
	minion->transform->position = { -36.94f,68.01f,-30.35f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionCaster>(Layer::Unit);
	minion->transform->position = { -36.68f,68.01f,-36.45f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { 23.98f,67.71f,-34.88f };
	minion->ai->wayPoint.push_back(Vector3(34.58f, 67.71f, -23.79f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;






}

void TestScene::CreateMinionMelee()
{
	Minion* minion = nullptr;
	// 블루========================================================
	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionMelee>(Layer::Unit);
	minion->transform->position = { 29.47f,68.04f,41.74f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -30.88f,67.71f,40.80f };
	minion->ai->wayPoint.push_back(Vector3(-42.32f, 67.71f, 28.58f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionMelee>(Layer::Unit);
	minion->transform->position = { 30.64f,68.04f,37.51f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionMelee>(Layer::Unit);
	minion->transform->position = { 35.00f,68.04f,35.55f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { 34.58f,67.71f,-23.79f };
	minion->ai->wayPoint.push_back(Vector3(23.98f, 67.71f, -34.88f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	// 레드
	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionMelee>(Layer::Unit);
	minion->transform->position = { -43.05f,68.01f,-29.62f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -42.32f,67.71f,28.58f };
	minion->ai->wayPoint.push_back(Vector3(-30.88f, 67.71f, 40.80f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionMelee>(Layer::Unit);
	minion->transform->position = { -36.94f,68.01f,-30.35f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionMelee>(Layer::Unit);
	minion->transform->position = { -36.68f,68.01f,-36.45f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { 23.98f,67.71f,-34.88f };
	minion->ai->wayPoint.push_back(Vector3(34.58f, 67.71f, -23.79f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;
}

void TestScene::CreateMinionSiege()
{
	Minion* minion = nullptr;
	// 블루
	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionSiege>(Layer::Unit);
	minion->transform->position = { 29.47f,68.04f,41.74f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -30.88f,67.71f,40.80f };
	minion->ai->wayPoint.push_back(Vector3(-42.32f, 67.71f, 28.58f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionSiege>(Layer::Unit);
	minion->transform->position = { 30.64f,68.04f,37.51f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionSiege>(Layer::Unit);
	minion->transform->position = { 35.00f,68.04f,35.55f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { 34.58f,67.71f,-23.79f };
	minion->ai->wayPoint.push_back(Vector3(23.98f, 67.71f, -34.88f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	// 레드
	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionSiege>(Layer::Unit);
	minion->transform->position = { -43.05f,68.01f,-29.62f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -42.32f,67.71f,28.58f };
	minion->ai->wayPoint.push_back(Vector3(-30.88f, 67.71f, 40.80f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionSiege>(Layer::Unit);
	minion->transform->position = { -36.94f,68.01f,-30.35f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionSiege>(Layer::Unit);
	minion->transform->position = { -36.68f,68.01f,-36.45f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { 23.98f,67.71f,-34.88f };
	minion->ai->wayPoint.push_back(Vector3(34.58f, 67.71f, -23.79f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;
}

void TestScene::CreateMinionSuper()
{
	Minion* minion = nullptr;
	// 블루
	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionSuper>(Layer::Unit);
	minion->transform->position = { 29.47f,68.04f,41.74f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -30.88f,67.71f,40.80f };
	minion->ai->wayPoint.push_back(Vector3(-42.32f, 67.71f, 28.58f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionSuper>(Layer::Unit);
	minion->transform->position = { 30.64f,68.04f,37.51f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionSuper>(Layer::Unit);
	minion->transform->position = { 35.00f,68.04f,35.55f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { 34.58f,67.71f,-23.79f };
	minion->ai->wayPoint.push_back(Vector3(23.98f, 67.71f, -34.88f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	// 레드
	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionSuper>(Layer::Unit);
	minion->transform->position = { -43.05f,68.01f,-29.62f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -42.32f,67.71f,28.58f };
	minion->ai->wayPoint.push_back(Vector3(-30.88f, 67.71f, 40.80f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionSuper>(Layer::Unit);
	minion->transform->position = { -36.94f,68.01f,-30.35f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;

	minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionSuper>(Layer::Unit);
	minion->transform->position = { -36.68f,68.01f,-36.45f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { 23.98f,67.71f,-34.88f };
	minion->ai->wayPoint.push_back(Vector3(34.58f, 67.71f, -23.79f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
	unitMap[unitID] = minion;
	minion->SetID(unitID);
	unitID++;
}
