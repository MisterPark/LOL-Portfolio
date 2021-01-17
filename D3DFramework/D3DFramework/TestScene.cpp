#include "stdafx.h"
#include "TestScene.h"

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


	GameObject* obj = nullptr;
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
	obj = ObjectManager::GetInstance()->CreateObject<RedMonster>(Layer::EnemyUnit);
	obj->transform->position = { -6.10,67.71,24.87 };
	obj = ObjectManager::GetInstance()->CreateObject<RedMonster>(Layer::EnemyUnit);
	obj->transform->position = { -1.88,67.71,-17.87 };
	// ºí·ç
	obj = ObjectManager::GetInstance()->CreateObject<BlueMonster>(Layer::EnemyUnit);
	obj->transform->position = { 19.79,67.72,0.64 };
	obj = ObjectManager::GetInstance()->CreateObject<BlueMonster>(Layer::EnemyUnit);
	obj->transform->position = { -26.43,67.71,6.83 };
	// ´Á´ë À§
	obj = ObjectManager::GetInstance()->CreateObject<Murkwolf>();
	obj->transform->position = { 19.74,67.71,9.78 };
	obj = ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::EnemyUnit);
	obj->transform->position = { 19.17,67.71,10.84 };
	obj = ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::EnemyUnit);
	obj->transform->position = { 21.08,67.71,9.00 };
	// ´Á´ë ¾Æ·¡
	obj = ObjectManager::GetInstance()->CreateObject<Murkwolf>(Layer::EnemyUnit);
	obj->transform->position = { -26.72,67.72,-2.72 };
	obj = ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::EnemyUnit);
	obj->transform->position = { -26.23,67.71,-3.57 };
	obj = ObjectManager::GetInstance()->CreateObject<MurkwolfMini>(Layer::EnemyUnit);
	obj->transform->position = { -27.73,67.71,-2.44 };
	// µÎ²¨ºñ
	obj = ObjectManager::GetInstance()->CreateObject<Gromp>(Layer::EnemyUnit);
	obj->transform->position = { 29.28,67.73,-2.82 };
	obj = ObjectManager::GetInstance()->CreateObject<Gromp>(Layer::EnemyUnit);
	obj->transform->position = { -36.59,67.71,10.14 };

	// ¤‹¤‹ÀÌ À§
	obj = ObjectManager::GetInstance()->CreateObject<Razorbeak>(Layer::EnemyUnit);
	obj->transform->position = { -0.75,67.71,16.17 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::EnemyUnit);
	obj->transform->position = { -1.32,67.71,15.52 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::EnemyUnit);
	obj->transform->position = { -1.69,67.71,16.20 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::EnemyUnit);
	obj->transform->position = { -1.71,67.71,17.11 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::EnemyUnit);
	obj->transform->position = { -0.98,67.71,17.65 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::EnemyUnit);
	obj->transform->position = { 0.08,67.71,17.21 };

	// Â±Â±ÀÌ ¾Æ·¡
	obj = ObjectManager::GetInstance()->CreateObject<Razorbeak>(Layer::EnemyUnit);
	obj->transform->position = { -6.43,67.71,-10.09 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::EnemyUnit);
	obj->transform->position = { -5.53,67.71,-9.14 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::EnemyUnit);
	obj->transform->position = { -5.56,67.71,-10.09 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::EnemyUnit);
	obj->transform->position = { -5.91,67.71,-11.04 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::EnemyUnit);
	obj->transform->position = { -6.81,67.71,-10.93 };
	obj = ObjectManager::GetInstance()->CreateObject<RazorbeakMini>(Layer::EnemyUnit);
	obj->transform->position = { -7.31,67.71,-10.48 };


	// ÀÛ°ñ
	obj = ObjectManager::GetInstance()->CreateObject<Krug>(Layer::EnemyUnit);
	obj->transform->position = { -10.05,67.71,33.49 };

	obj = ObjectManager::GetInstance()->CreateObject<Krug>(Layer::EnemyUnit);
	obj->transform->position = { 3.13,67.71,-26.61 };

	// ¹ÙÀ§°Ô
	obj = ObjectManager::GetInstance()->CreateObject<Scuttleracer>(Layer::EnemyUnit);
	obj->transform->position = { 15.68,66.91,-11.16 };

	obj = ObjectManager::GetInstance()->CreateObject<Scuttleracer>(Layer::EnemyUnit);
	obj->transform->position = { -24.36,66.91,17.82 };


	// Ã¨ÇÇ¾ð
	obj = ObjectManager::GetInstance()->CreateObject<Garen>(Layer::TeamUnit);
	obj->transform->position = { 41,68,46 };
	obj->AddComponent<PlayerController>(L"PlayerController");
	Camera::GetInstance()->SetTarget(obj);

	

	obj = PlayerInfoPanel::GetInstance();
	ObjectManager::GetInstance()->AddObject(obj, Layer::UI);
	

	obj = ObjectManager::GetInstance()->CreateObject<Blitzcrank>(Layer::EnemyUnit);
	obj->transform->position = { 32,68,29 };
	//obj->AddComponent<PlayerController>(L"PlayerController");
	obj = ObjectManager::GetInstance()->CreateObject<Darius>(Layer::EnemyUnit);
	obj->transform->position = { 29,68,30 };
	//obj->AddComponent<PlayerController>(L"PlayerController");
	obj = ObjectManager::GetInstance()->CreateObject<Diana>(Layer::EnemyUnit);
	obj->transform->position = { 26,68,32 };
	//obj->AddComponent<PlayerController>(L"PlayerController");
	obj = ObjectManager::GetInstance()->CreateObject<Leesin>(Layer::EnemyUnit);
	obj->transform->position = { 24,68,34 };
	//obj->AddComponent<PlayerController>(L"PlayerController");
	obj = ObjectManager::GetInstance()->CreateObject<Missfortune>(Layer::EnemyUnit);
	obj->transform->position = { 23,68,37 };
	//obj->AddComponent<PlayerController>(L"PlayerController");
	obj = ObjectManager::GetInstance()->CreateObject<Leona>(Layer::EnemyUnit);
	obj->transform->position = { 30,68,27 };
	//obj->AddComponent<PlayerController>(L"PlayerController");
	obj = ObjectManager::GetInstance()->CreateObject<Ahri>(Layer::EnemyUnit);
	obj->transform->position = { 31,68,28 };
	//obj->AddComponent<PlayerController>(L"PlayerController");

	// ÆÛÇÃÆÀ
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { -38.39f,67.87f,-29.67f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { -37.14f,67.87f,-33.51f };

	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { -42.44f,67.87f,-16.78f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { -26.67f,67.87f,-20.54f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { -23.36f,67.87f,-37.31f };

	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { -39.68f,67.71f,-2.57f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { -18.84f,67.71f,-13.95f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { -7.48f,67.71f,-33.31f };

	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { -45.25f,67.71f,22.31f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { -14.04f,67.71f,-3.74f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { 15.71f,67.71f,-37.53f };

	// ºí·çÆÀ Å¸¿ö
	// twin Right
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { 29.46f, 68.f, 39.3f };
	obj->transform->eulerAngles.y = D3DXToRadian(90.f);
	// twin Left
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { 32.35f, 68.f, 36.f };
	obj->transform->eulerAngles.y = D3DXToRadian(90.f);

	// bottom1
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { -23.15f, 67.71f, 44.17f };
	obj->transform->eulerAngles.y = D3DXToRadian(135.f);
	// bottom2
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { -0.30f, 67.71f, 41.20f };
	obj->transform->eulerAngles.y = D3DXToRadian(135.f);
	// bottom3
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { 16.41f, 67.87f, 42.5f };
	obj->transform->eulerAngles.y = D3DXToRadian(135.f);
	
	// mid1
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { 6.50f, 67.71f, 10.f };
	obj->transform->eulerAngles.y = D3DXToRadian(90.f);
	// mid2
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { 11.61f, 67.71f, 20.f };
	obj->transform->eulerAngles.y = D3DXToRadian(90.f);
	// mid3
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { 20.51f, 67.87f, 27.f };
	obj->transform->eulerAngles.y = D3DXToRadian(90.f);

	// top1
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { 37.42f, 67.71f, -16.f };
	obj->transform->eulerAngles.y = D3DXToRadian(45.f);
	// top2
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { 34.12f, 67.71f, 8.f };
	obj->transform->eulerAngles.y = D3DXToRadian(45.f);
	
	// top3
	obj = ObjectManager::GetInstance()->CreateObject<Turret>(Layer::EnemyUnit);
	obj->transform->position = { 36.36f, 67.87f, 23.f };
	obj->transform->eulerAngles.y = D3DXToRadian(45.f);



	// ¹Ì´Ï¾ð
	obj = ObjectManager::GetInstance()->CreateObject<OrderMinionCaster>(Layer::EnemyUnit);
	obj->transform->position = { 26,68,38 };
	obj = ObjectManager::GetInstance()->CreateObject<OrderMinionMelee>(Layer::EnemyUnit);
	obj->transform->position = { 23,68,38 };
	obj = ObjectManager::GetInstance()->CreateObject<OrderMinionSiege>(Layer::EnemyUnit);
	obj->transform->position = { 20,68,38 };
	obj = ObjectManager::GetInstance()->CreateObject<OrderMinionSuper>(Layer::EnemyUnit);
	obj->transform->position = { 17,68,38 };

	obj = ObjectManager::GetInstance()->CreateObject<ChaosMinionCaster>(Layer::EnemyUnit);
	obj->transform->position = { 26,68,39 };
	obj = ObjectManager::GetInstance()->CreateObject<ChaosMinionMelee>(Layer::EnemyUnit);
	obj->transform->position = { 23,68,39 };
	obj = ObjectManager::GetInstance()->CreateObject<ChaosMinionSiege>(Layer::EnemyUnit);
	obj->transform->position = { 20,68,39 };
	obj = ObjectManager::GetInstance()->CreateObject<ChaosMinionSuper>(Layer::EnemyUnit);
	obj->transform->position = { 17,68,39 };
}

void TestScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void TestScene::Update()
{

}