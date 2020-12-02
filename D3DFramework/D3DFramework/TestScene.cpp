#include "stdafx.h"
#include "TestScene.h"
#include "SkyBox.h"
#include "Environment.h"
#include "TestMan.h"
#include "PlayerController.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

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

	obj = ObjectManager::GetInstance()->CreateObject<TestMan>();
	obj->transform->scale = { 0.003f,0.003f, 0.003f };
	obj->transform->position = { 0,0,0 };
	obj->AddComponent<PlayerController>(L"PlayerController");

	obj = ObjectManager::GetInstance()->CreateObject<TestMan>();
	obj->transform->scale = { 0.003f,0.003f, 0.003f };
	obj->transform->position = { 2,0,2 };
	

	//obj = ObjectManager::GetInstance()->CreateObject<TestMan>();
	//obj->transform->scale = { 0.1f,0.1f, 0.1f };
	//obj->transform->position = { -10,0,0 };

	//obj = ObjectManager::GetInstance()->CreateObject<TestMan>();
	//obj->transform->scale = { 0.1f,0.1f, 0.1f };
	//obj->transform->position = { 20,0,0 };

	//obj = ObjectManager::GetInstance()->CreateObject<TestMan>();
	//obj->transform->scale = { 0.1f,0.1f, 0.1f };
	//obj->transform->position = { -20,0,0 };

	//obj = ObjectManager::GetInstance()->CreateObject<TestMan>();
	//obj->transform->scale = { 0.1f,0.1f, 0.1f };
	//obj->transform->position = { 10,0,10 };
}

void TestScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void TestScene::Update()
{

}