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

#include "Garen.h"
#include "Blitzcrank.h"
#include "Darius.h"
#include "Diana.h"
#include "Leesin.h"
#include "Missfortune.h"

void TestScene::OnLoaded()
{
	Cursor::Show();
	//ObjectManager::GetInstance()->CreateObject<Light>();

	//SkyBox::Show();
	//SkyBox::SetTexture(TextureKey::SKY_U);
	Camera::GetInstance()->SetPosition(Vector3(0.f, 1.f ,-1.f));
	Camera::GetInstance()->transform->look = Vector3(0, 0, 1);


	GameObject* obj = nullptr;
	obj = ObjectManager::GetInstance()->CreateObject<Environment>();
	obj->transform->position = { 0,0,0 };

	obj = ObjectManager::GetInstance()->CreateObject<NavMeshMap>(Layer::Ground);

	obj = ObjectManager::GetInstance()->CreateObject<Wall>(Layer::Wall);


	obj = ObjectManager::GetInstance()->CreateObject<Garen>();
	obj->transform->position = { 41,68,46 };
	obj->AddComponent<PlayerController>(L"PlayerController");
	Camera::GetInstance()->SetTarget(obj);

	obj = ObjectManager::GetInstance()->CreateObject<Blitzcrank>();
	obj->transform->position = { 32,68,29 };
	obj = ObjectManager::GetInstance()->CreateObject<Darius>();
	obj->transform->position = { 29,68,30 };
	obj = ObjectManager::GetInstance()->CreateObject<Diana>();
	obj->transform->position = { 26,68,32 };
	obj = ObjectManager::GetInstance()->CreateObject<Leesin>();
	obj->transform->position = { 24,68,34 };
	obj = ObjectManager::GetInstance()->CreateObject<Missfortune>();
	obj->transform->position = { 23,68,37 };

	// ÆÛÇÃÆÀ
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { -38.39f,67.87f,-29.67f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { -37.14f,67.87f,-33.51f };

	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { -42.44f,67.87f,-16.78f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { -26.67f,67.87f,-20.54f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { -23.36f,67.87f,-37.31f };

	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { -39.68f,67.71f,-2.57f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { -18.84f,67.71f,-13.95f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { -7.48f,67.71f,-33.31f };

	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { -45.25f,67.71f,22.31f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { -14.04f,67.71f,-3.74f };
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { 15.71f,67.71f,-37.53f };

	// ºí·çÆÀ Å¸¿ö
	// twin Right
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { 29.46f, 68.f, 39.3f };
	obj->transform->eulerAngles.y = D3DXToRadian(90.f);
	// twin Left
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { 32.35f, 68.f, 36.f };
	obj->transform->eulerAngles.y = D3DXToRadian(90.f);

	// bottom1
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { -23.15f, 67.71f, 44.17f };
	obj->transform->eulerAngles.y = D3DXToRadian(135.f);
	// bottom2
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { -0.30f, 67.71f, 41.20f };
	obj->transform->eulerAngles.y = D3DXToRadian(135.f);
	// bottom3
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { 16.41f, 67.87f, 42.5f };
	obj->transform->eulerAngles.y = D3DXToRadian(135.f);
	
	// mid1
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { 6.50f, 67.71f, 10.f };
	obj->transform->eulerAngles.y = D3DXToRadian(90.f);
	// mid2
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { 11.61f, 67.71f, 20.f };
	obj->transform->eulerAngles.y = D3DXToRadian(90.f);
	// mid3
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { 20.51f, 67.87f, 27.f };
	obj->transform->eulerAngles.y = D3DXToRadian(90.f);

	// top1
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { 37.42f, 67.71f, -16.f };
	obj->transform->eulerAngles.y = D3DXToRadian(45.f);
	// top2
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { 34.12f, 67.71f, 8.f };
	obj->transform->eulerAngles.y = D3DXToRadian(45.f);
	
	// top3
	obj = ObjectManager::GetInstance()->CreateObject<Turret>();
	obj->transform->position = { 36.36f, 67.87f, 23.f };
	obj->transform->eulerAngles.y = D3DXToRadian(45.f);

}

void TestScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void TestScene::Update()
{

}