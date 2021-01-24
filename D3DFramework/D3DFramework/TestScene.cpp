#include "stdafx.h"
#include "TestScene.h"

#include "Label.h"

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

void TestScene::OnLoaded()
{
	Cursor::Show();
	//ObjectManager::GetInstance()->CreateObject<Light>();

	//SkyBox::Show();
	//SkyBox::SetTexture(TextureKey::SKY_U);
	Camera::GetInstance()->SetPosition(Vector3(0.f, 1.f ,-1.f));
	Camera::GetInstance()->transform->look = Vector3(0, 0, 1);

	testLabel = (Label*)ObjectManager::GetInstance()->CreateObject<Label>(Layer::UI);
	testLabel->text = L"123123";
	testLabel->foreColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	GameObject* obj = nullptr;
	Unit* unit = nullptr;
	// ¿ÀºêÁ§Æ®
	obj = ObjectManager::GetInstance()->CreateObject<Environment>();
	obj->transform->position = { 0,0,0 };

	// ¹Ù´Ú
	obj = ObjectManager::GetInstance()->CreateObject<NavMeshMap>(Layer::Ground);

	// º®
	obj = ObjectManager::GetInstance()->CreateObject<Wall>(Layer::Wall);

	// ºÎ½¬
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.98f,67.71f,29.14f };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.90,67.71,29.87 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.84,67.71,29.55 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.50,67.71,28.95 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.90,67.71,28.73 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.70,67.71,28.37 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.39,67.71,28.22 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 8.01,67.71,28.06 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.71,67.71,27.92 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.41,67.71,27.83 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.99,67.71,28.52 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.54,67.71,28.44 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.68,67.71,28.77 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.15,67.71,28.61 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 7.00,67.71,28.84 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 6.83,67.71,28.54 };
	obj = ObjectManager::GetInstance()->CreateObject<Bush>(Layer::Bush);
	obj->transform->position = { 6.99,67.71,28.18 };

	// ¸ó½ºÅÍ

	// ·¹µå
	obj = ObjectManager::GetInstance()->CreateObject<RedMonster>(Layer::Unit);
	obj->transform->position = { -6.10,67.71,24.87 };
	obj = ObjectManager::GetInstance()->CreateObject<RedMonster>(Layer::Unit);
	obj->transform->position = { -1.88,67.71,-17.87 };
	// ºí·ç
	obj = ObjectManager::GetInstance()->CreateObject<BlueMonster>(Layer::Unit);
	obj->transform->position = { 19.79,67.72,0.64 };
	obj = ObjectManager::GetInstance()->CreateObject<BlueMonster>(Layer::Unit);
	obj->transform->position = { -26.43,67.71,6.83 };
	// ´Á´ë À§
	obj = ObjectManager::GetInstance()->CreateObject<Murkwolf>();
	obj->transform->position = { 19.74,67.71,9.78 };
	obj = ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::Unit);
	obj->transform->position = { 19.17,67.71,10.84 };
	obj = ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::Unit);
	obj->transform->position = { 21.08,67.71,9.00 };
	// ´Á´ë ¾Æ·¡
	obj = ObjectManager::GetInstance()->CreateObject<Murkwolf>(Layer::Unit);
	obj->transform->position = { -26.72,67.72,-2.72 };
	obj = ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::Unit);
	obj->transform->position = { -26.23,67.71,-3.57 };
	obj = ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::Unit);
	obj->transform->position = { -27.73,67.71,-2.44 };
	// µÎ²¨ºñ
	obj = ObjectManager::GetInstance()->CreateObject<Gromp>(Layer::Unit);
	obj->transform->position = { 29.28,67.73,-2.82 };
	obj = ObjectManager::GetInstance()->CreateObject<Gromp>(Layer::Unit);
	obj->transform->position = { -36.59,67.71,10.14 };

	// ¤‹¤‹ÀÌ À§
	obj = ObjectManager::GetInstance()->CreateObject<Razorbeak>(Layer::Unit);
	obj->transform->position = { -0.75,67.71,16.17 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -1.32,67.71,15.52 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -1.69,67.71,16.20 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -1.71,67.71,17.11 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -0.98,67.71,17.65 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { 0.08,67.71,17.21 };

	// Â±Â±ÀÌ ¾Æ·¡
	obj = ObjectManager::GetInstance()->CreateObject<Razorbeak>(Layer::Unit);
	obj->transform->position = { -6.43,67.71,-10.09 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -5.53,67.71,-9.14 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -5.56,67.71,-10.09 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -5.91,67.71,-11.04 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -6.81,67.71,-10.93 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::Unit);
	obj->transform->position = { -7.31,67.71,-10.48 };


	// ÀÛ°ñ
	obj = ObjectManager::GetInstance()->CreateObject<Krug>(Layer::Unit);
	obj->transform->position = { -10.05,67.71,33.49 };

	obj = ObjectManager::GetInstance()->CreateObject<Krug>(Layer::Unit);
	obj->transform->position = { 3.13,67.71,-26.61 };

	// ¹ÙÀ§°Ô
	obj = ObjectManager::GetInstance()->CreateObject<Scuttleracer>(Layer::Unit);
	obj->transform->position = { 15.68,66.91,-11.16 };

	obj = ObjectManager::GetInstance()->CreateObject<Scuttleracer>(Layer::Unit);
	obj->transform->position = { -24.36,66.91,17.82 };


	// Ã¨ÇÇ¾ð
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Garen>(Layer::Unit);
	unit->transform->position = { 41,68,46 };
	unit->SetTeam(Team::BLUE);
	unit->AddComponent<PlayerController>(L"PlayerController");
	Camera::GetInstance()->SetTarget(unit);

	

	obj = PlayerInfoPanel::GetInstance();
	ObjectManager::GetInstance()->AddObject(obj, Layer::UI);
	

	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Blitzcrank>(Layer::Unit);
	unit->transform->position = { 32,68,29 };
	unit->SetTeam(Team::RED);
	//unit->AddComponent<PlayerController>(L"PlayerController");
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Darius>(Layer::Unit);
	unit->transform->position = { 29,68,30 };
	unit->SetTeam(Team::RED);
	//unit->AddComponent<PlayerController>(L"PlayerController");
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Diana>(Layer::Unit);
	unit->transform->position = { 26,68,32 };
	unit->SetTeam(Team::RED);
	//unit->AddComponent<PlayerController>(L"PlayerController");
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Leesin>(Layer::Unit);
	unit->transform->position = { 24,68,34 };
	unit->SetTeam(Team::RED);
	//unit->AddComponent<PlayerController>(L"PlayerController");
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Missfortune>(Layer::Unit);
	unit->transform->position = { 23,68,37 };
	unit->SetTeam(Team::RED);
	//unit->AddComponent<PlayerController>(L"PlayerController");
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Leona>(Layer::Unit);
	unit->transform->position = { 30,68,27 };
	unit->SetTeam(Team::RED);
	//unit->AddComponent<PlayerController>(L"PlayerController");
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Ahri>(Layer::Unit);
	unit->transform->position = { 31,68,28 };
	unit->SetTeam(Team::RED);
	//unit->AddComponent<PlayerController>(L"PlayerController");
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Jax>(Layer::Unit);
	unit->transform->position = { 29,68,28 };
	unit->SetTeam(Team::RED);
	//unit->AddComponent<PlayerController>(L"PlayerController");
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Jinx>(Layer::Unit);
	unit->transform->position = { 27,68,28 };
	unit->SetTeam(Team::RED);
	//unit->AddComponent<PlayerController>(L"PlayerController");

	// ºí·çÆÀ Å¸¿ö

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

	// ÆÛÇÃÆÀ

	// bottom1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -45.25f,67.71f,22.31f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	// bottom2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -39.68f,67.71f,-2.57f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);
	// bottom3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -42.44f,67.87f,-16.78f };
	unit->transform->eulerAngles.y = D3DXToRadian(225.f);
	unit->SetTeam(Team::RED);

	// mid1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -14.04f,67.71f,-3.74f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	// mid2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -18.84f,67.71f,-13.95f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	// mid3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -26.67f,67.87f,-20.54f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);

	// top1
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { 15.71f,67.71f,-37.53f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	// top2
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -7.48f,67.71f,-33.31f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);
	// top3
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -23.36f,67.87f,-37.31f };
	unit->transform->eulerAngles.y = D3DXToRadian(315.f);
	unit->SetTeam(Team::RED);


	// twin left
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -38.39f,67.87f,-29.67f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);
	// twin right
	unit = (Unit*)ObjectManager::GetInstance()->CreateObject<Turret>(Layer::Building);
	unit->transform->position = { -37.14f,67.87f,-33.51f };
	unit->transform->eulerAngles.y = D3DXToRadian(270.f);
	unit->SetTeam(Team::RED);



	// ¹Ì´Ï¾ð
	obj = ObjectManager::GetInstance()->CreateObject<OrderMinionCaster>(Layer::Unit);
	obj->transform->position = { 26,68,38 };
	obj = ObjectManager::GetInstance()->CreateObject<OrderMinionMelee>(Layer::Unit);
	obj->transform->position = { 23,68,38 };
	obj = ObjectManager::GetInstance()->CreateObject<OrderMinionSiege>(Layer::Unit);
	obj->transform->position = { 20,68,38 };
	obj = ObjectManager::GetInstance()->CreateObject<OrderMinionSuper>(Layer::Unit);
	obj->transform->position = { 17,68,38 };

	obj = ObjectManager::GetInstance()->CreateObject<ChaosMinionCaster>(Layer::Unit);
	obj->transform->position = { 26,68,39 };
	obj = ObjectManager::GetInstance()->CreateObject<ChaosMinionMelee>(Layer::Unit);
	obj->transform->position = { 23,68,39 };
	obj = ObjectManager::GetInstance()->CreateObject<ChaosMinionSiege>(Layer::Unit);
	obj->transform->position = { 20,68,39 };
	obj = ObjectManager::GetInstance()->CreateObject<ChaosMinionSuper>(Layer::Unit);
	obj->transform->position = { 17,68,39 };
}

void TestScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void TestScene::Update()
{

}