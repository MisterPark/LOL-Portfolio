#include "stdafx.h"
#include "TestScene.h"

#include "Label.h"
#include "MinimapPanel.h"

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

#include "Garen.h"
#include "Blitzcrank.h"
#include "Darius.h"
#include "Diana.h"
#include "Leesin.h"
#include "Missfortune.h"
#include "Leona.h"
#include "Ahri.h"
#include "Jax.h"
#include "Jinx.h"

#include "PlayerInfoPanel.h"
#include "FloatingBar.h"

#include "OrderMinionCaster.h"
#include "OrderMinionMelee.h"
#include "OrderMinionSiege.h"
#include "OrderMinionSuper.h"
#include "ChaosMinionCaster.h"
#include "ChaosMinionSiege.h"
#include "ChaosMinionSuper.h"
#include "ChaosMinionMelee.h"

#include "BlueMonster.h"
#include "RedMonster.h"
#include "Murkwolf.h"
#include "MurkwolfMini.h"
#include "Krug.h"
#include "KrugMini.h"
#include "Gromp.h"
#include "Razorbeak.h"
#include "RazorbeakMini.h"
#include "Scuttleracer.h"

#include "MonsterAI.h"

#include "Nexus.h"
#include "MinionAI.h"

#include "GameRenderer.h"
void TestScene::OnLoaded()
{
	Cursor::Show();
	//ObjectManager::GetInstance()->CreateObject<Light>();

	//SkyBox::Show();
	//SkyBox::SetTexture(TextureKey::SKY_U);
	Camera::GetInstance()->SetPosition(Vector3(0.f, 1.f ,-1.f));
	Camera::GetInstance()->transform->look = Vector3(0, 0, 1);

	testLabel = (Label*)ObjectManager::GetInstance()->CreateObject<Label>(Layer::UI);
	testLabel->text = L"123123\n123123";
	testLabel->foreColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	MinimapPanel* minimap = MinimapPanel::GetInstance();
	ObjectManager::GetInstance()->AddObject(minimap, Layer::HUD);

	GameObject* obj = nullptr;
	Unit* unit = nullptr;
	// ������Ʈ
	obj = ObjectManager::GetInstance()->CreateObject<Environment>();
	obj->transform->position = { 0,0,0 };

	// �ٴ�
	obj = ObjectManager::GetInstance()->CreateObject<NavMeshMap>(Layer::Ground);
	
	// ��
	obj = ObjectManager::GetInstance()->CreateObject<Wall>(Layer::Wall);

	// �ν�
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.98f,67.71f,29.14f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.90f, 67.71f, 29.87f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.84f, 67.71f, 29.55f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.50f, 67.71f, 28.95f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.90f, 67.71f, 28.73f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.70f, 67.71f, 28.37f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.39f, 67.71f, 28.22f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.01f, 67.71f, 28.06f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.71f, 67.71f, 27.92f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.41f, 67.71f, 27.83f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.99f, 67.71f, 28.52f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.54f, 67.71f, 28.44f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.68f, 67.71f, 28.77f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.15f, 67.71f, 28.61f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.00f, 67.71f, 28.84f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 6.83f, 67.71f, 28.54f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 6.99f, 67.71f, 28.18f };

	// ����

	// ����
	obj = ObjectManager::GetInstance()->CreateObject<RedMonster>(Layer::Unit);
	obj->transform->position = { -6.10f, 67.71f, 24.87f };
	obj = ObjectManager::GetInstance()->CreateObject<RedMonster>(Layer::Unit);
	obj->transform->position = { -1.88f, 67.71f, -17.87f };
	// ���
	obj = ObjectManager::GetInstance()->CreateObject<BlueMonster>(Layer::Unit);
	obj->transform->position = { 19.79f, 67.72f, 0.64f };
	obj = ObjectManager::GetInstance()->CreateObject<BlueMonster>(Layer::Unit);
	obj->transform->position = { -26.43f, 67.71f, 6.83f };
	// ���� ��
	obj = ObjectManager::GetInstance()->CreateObject<Murkwolf>(Layer::Unit);
	obj->transform->position = { 19.74f, 67.71f, 9.78f };
	obj = ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::Unit);
	obj->transform->position = { 19.17f, 67.71f, 10.84f };
	obj = ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::Unit);
	obj->transform->position = { 21.08f, 67.71f, 9.00f };
	// ���� �Ʒ�
	obj = ObjectManager::GetInstance()->CreateObject<Murkwolf>(Layer::Unit);
	obj->transform->position = { -26.72f, 67.72f, -2.72f };
	obj = ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::Unit);
	obj->transform->position = { -26.23f, 67.71f, -3.57f };
	obj = ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::Unit);
	obj->transform->position = { -27.73f, 67.71f, -2.44f };
	// �β���
	obj = ObjectManager::GetInstance()->CreateObject<Gromp>(Layer::Unit);
	obj->transform->position = { 29.28f, 67.73f, -2.82f };
	obj = ObjectManager::GetInstance()->CreateObject<Gromp>(Layer::Unit);
	obj->transform->position = { -36.59f, 67.71f, 10.14f };

	// ������ ��
	obj = ObjectManager::GetInstance()->CreateObject<Razorbeak>(Layer::Unit);
	obj->transform->position = { -0.75f, 67.71f, 16.17f };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -1.32f, 67.71f, 15.52f };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -1.69f, 67.71f, 16.20f };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -1.71f, 67.71f, 17.11f };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -0.98f, 67.71f, 17.65f };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { 0.08f, 67.71f, 17.21f };

	// ±±�� �Ʒ�
	obj = ObjectManager::GetInstance()->CreateObject<Razorbeak>(Layer::Unit);
	obj->transform->position = { -6.43f, 67.71f, -10.09f };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -5.53f, 67.71f, -9.14f };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -5.56f, 67.71f, -10.09f };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -5.91f, 67.71f, -11.04f };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -6.81f, 67.71f, -10.93f };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -7.31f, 67.71f, -10.48f };


	// �۰�
	obj = ObjectManager::GetInstance()->CreateObject<Krug>(Layer::Unit);
	obj->transform->position = { -10.05f, 67.71f, 33.49f };

	obj = ObjectManager::GetInstance()->CreateObject<Krug>(Layer::Unit);
	obj->transform->position = { 3.13f, 67.71f, -26.61f };

	// ������
	obj = ObjectManager::GetInstance()->CreateObject<Scuttleracer>(Layer::Unit);
	obj->transform->position = { 15.68f, 66.91f, -11.16f };

	obj = ObjectManager::GetInstance()->CreateObject<Scuttleracer>(Layer::Unit);
	obj->transform->position = { -24.36f, 66.91f, 17.82f };


	// è�Ǿ�
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Garen>(Layer::Unit);
	unit->transform->position = { 41,68,46 };
	unit->SetTeam(Team::BLUE);
	unit->AddComponent<PlayerController>(L"PlayerController");
	Camera::GetInstance()->SetTarget(unit);
	PlayerInfoPanel::GetInstance()->SetTarget((Champion*)unit);
	Champion* champ = (Champion*)unit;
	champ->bar->SetNickname(L"�׽�Ʈ�г���");
	

	obj = PlayerInfoPanel::GetInstance();
	ObjectManager::GetInstance()->AddObject(obj, Layer::HUD);
	

	//unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Blitzcrank>(Layer::Unit);
	//unit->transform->position = { 32,68,29 };
	//unit->SetTeam(Team::RED);
	////unit->AddComponent<PlayerController>(L"PlayerController");
	//unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Darius>(Layer::Unit);
	//unit->transform->position = { 29,68,30 };
	//unit->SetTeam(Team::RED);
	////unit->AddComponent<PlayerController>(L"PlayerController");
	//unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Diana>(Layer::Unit);
	//unit->transform->position = { 26,68,32 };
	//unit->SetTeam(Team::RED);
	////unit->AddComponent<PlayerController>(L"PlayerController");
	//unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Leesin>(Layer::Unit);
	//unit->transform->position = { 24,68,34 };
	//unit->SetTeam(Team::RED);
	////unit->AddComponent<PlayerController>(L"PlayerController");
	//unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Missfortune>(Layer::Unit);
	//unit->transform->position = { 23,68,37 };
	//unit->SetTeam(Team::RED);
	////unit->AddComponent<PlayerController>(L"PlayerController");
	//unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Leona>(Layer::Unit);
	//unit->transform->position = { 30,68,27 };
	//unit->SetTeam(Team::RED);
	////unit->AddComponent<PlayerController>(L"PlayerController");
	//unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Ahri>(Layer::Unit);
	//unit->transform->position = { 31,68,28 };
	//unit->SetTeam(Team::RED);
	////unit->AddComponent<PlayerController>(L"PlayerController");
	//unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Jax>(Layer::Unit);
	//unit->transform->position = { 29,68,28 };
	//unit->SetTeam(Team::RED);
	//unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Jinx>(Layer::Unit);
	//unit->transform->position = { 27,68,28 };
	//unit->SetTeam(Team::RED);
	//unit->AddComponent<PlayerController>(L"PlayerController");
	//Camera::GetInstance()->SetTarget(unit);
	//unit->AddComponent<PlayerController>(L"PlayerController");


	// ����� Ÿ��

	// bottom1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -23.15f, 67.71f, 44.17f };
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);
	// bottom2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -0.30f, 67.71f, 41.20f };
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);
	// bottom3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 16.41f, 67.87f, 42.5f };
	unit->transform->eulerAngles.y = D3DXToRadian(135.f);
	unit->SetTeam(Team::BLUE);

	// mid1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 6.50f, 67.71f, 10.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	
	// mid2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 11.61f, 67.71f, 20.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	// mid3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 20.51f, 67.87f, 27.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);

	// top1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 37.42f, 67.71f, -16.f };
	unit->transform->eulerAngles.y = D3DXToRadian(45.f);
	unit->SetTeam(Team::BLUE);
	// top2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 34.12f, 67.71f, 8.f };
	unit->transform->eulerAngles.y = D3DXToRadian(45.f);
	unit->SetTeam(Team::BLUE);

	// top3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 36.36f, 67.87f, 23.f };
	unit->transform->eulerAngles.y = D3DXToRadian(45.f);
	unit->SetTeam(Team::BLUE);


	// twin Left
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 32.35f, 68.f, 36.f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	// twin Right
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 29.46f, 68.f, 39.3f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);

	// nexus
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Nexus>(Layer::Building);
	unit->transform->position = { 33.90f,68.04f,39.89f };
	unit->transform->eulerAngles.y = D3DXToRadian(90.f);
	unit->SetTeam(Team::BLUE);
	

	// ������

	// bottom1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -44.71f,67.71f,21.98f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	// bottom2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -41.30f,67.71f,-1.89f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	// bottom3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -43.20f,68.f,-16.83f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);

	// mid1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -13.30f,67.71f,-3.61f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	
	// mid2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -18.52f,67.71f,-13.85f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	
	// mid3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -27.21f,68.f,-20.97f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	

	// top1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 16.28f,67.71f,-37.99f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	// top2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -6.93f,67.71f,-34.96f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	// top3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -23.09f,68.f,-36.63f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);

	// twin left
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -39.52f,68.00f,-29.97f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	// twin right
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -36.64f,68.00f,-32.90f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	//testUnit = unit;

	D3DLIGHT9 dirLight{};
	Vector3 v = Vector3(1.f, -1.f, 1.f).Normalized();
	dirLight.Type = D3DLIGHT_DIRECTIONAL;
	dirLight.Direction = v;
	dirLight.Diffuse = D3DCOLORVALUE{ 1.f, 1.f, 1.f, 1.f };
	dirLight.Ambient = D3DCOLORVALUE{ 0.2f, 0.2f, 0.2f, 1.0f};
	GameRenderer::AddLight(L"dir1", dirLight);

	// �̴Ͼ�
	

	//obj = ObjectManager::GetInstance()->CreateObject<OrderMinionMelee>(Layer::Unit);
	//obj->transform->position = { 23,68,38 };
	//obj = ObjectManager::GetInstance()->CreateObject<OrderMinionSiege>(Layer::Unit);
	//obj->transform->position = { 20,68,38 };
	//obj = ObjectManager::GetInstance()->CreateObject<OrderMinionSuper>(Layer::Unit);
	//obj->transform->position = { 17,68,38 };
	//
	//obj = ObjectManager::GetInstance()->CreateObject<ChaosMinionCaster>(Layer::Unit);
	//obj->transform->position = { 26,68,39 };
	//obj = ObjectManager::GetInstance()->CreateObject<ChaosMinionMelee>(Layer::Unit);
	//obj->transform->position = { 23,68,39 };
	//obj = ObjectManager::GetInstance()->CreateObject<ChaosMinionSiege>(Layer::Unit);
	//obj->transform->position = { 20,68,39 };
	//obj = ObjectManager::GetInstance()->CreateObject<ChaosMinionSuper>(Layer::Unit);
	//obj->transform->position = { 17,68,39 };
}

void TestScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void TestScene::Update()
{
	if (testUnit != nullptr)
	{
		if (InputManager::GetKey(VK_UP))
		{
			testUnit->transform->position.z -= TimeManager::DeltaTime();
			printf("%.2ff,%.2ff,%.2ff\n", testUnit->transform->position.x, testUnit->transform->position.y, testUnit->transform->position.z);

		}
		if (InputManager::GetKey(VK_DOWN))
		{
			testUnit->transform->position.z += TimeManager::DeltaTime();
			printf("%.2ff,%.2ff,%.2ff\n", testUnit->transform->position.x, testUnit->transform->position.y, testUnit->transform->position.z);

		}
		if (InputManager::GetKey(VK_LEFT))
		{
			testUnit->transform->position.x += TimeManager::DeltaTime();
			printf("%.2ff,%.2ff,%.2ff\n", testUnit->transform->position.x, testUnit->transform->position.y, testUnit->transform->position.z);

		}
		if (InputManager::GetKey(VK_RIGHT))
		{
			testUnit->transform->position.x -= TimeManager::DeltaTime();
			printf("%.2ff,%.2ff,%.2ff\n", testUnit->transform->position.x, testUnit->transform->position.y, testUnit->transform->position.z);

		}
	}
	
	if (InputManager::GetKeyDown('M'))
	{
		CreateMinionCaster();
	}
}

void TestScene::CreateMinionCaster()
{
	Minion* minion = nullptr;
	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionCaster>(Layer::Unit);
	minion->transform->position = { 29.47f,68.04f,41.74f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -30.88f,67.71f,40.80f };
	minion->ai->wayPoint.push_back(Vector3(-42.32f, 67.71f, 28.58f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionCaster>(Layer::Unit);
	minion->transform->position = { 30.64f,68.04f,37.51f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<OrderMinionCaster>(Layer::Unit);
	minion->transform->position = { 35.00f,68.04f,35.55f };
	minion->SetTeam(Team::BLUE);
	minion->ai->nextPoint = { 34.58f,67.71f,-23.79f };
	minion->ai->wayPoint.push_back(Vector3(23.98f, 67.71f, -34.88f));
	minion->ai->wayPoint.push_back(Vector3(-42.87f, 68.01f, -36.16f));

	// ����
	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionCaster>(Layer::Unit);
	minion->transform->position = { -43.05f,68.01f,-29.62f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -42.32f,67.71f,28.58f };
	minion->ai->wayPoint.push_back(Vector3(-30.88f, 67.71f, 40.80f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionCaster>(Layer::Unit);
	minion->transform->position = { -36.94f,68.01f,-30.35f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { -3.49f,67.72f,3.92f };
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));

	minion = (Minion*)ObjectManager::GetInstance()->CreateObject<ChaosMinionCaster>(Layer::Unit);
	minion->transform->position = { -36.68f,68.01f,-36.45f };
	minion->SetTeam(Team::RED);
	minion->ai->nextPoint = { 23.98f,67.71f,-34.88f };
	minion->ai->wayPoint.push_back(Vector3(34.58f, 67.71f, -23.79f));
	minion->ai->wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
}
