#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"
#include "Triangle.h"


void TestScene::OnLoaded()
{
	Player*  p = (Player*)ObjectManager::GetInstance()->CreateObject<Player>();
	p->AddComponent<Triangle>(L"Mesh");
}

void TestScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void TestScene::Update()
{
}
