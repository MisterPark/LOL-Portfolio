#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Cube.h"
#include "Monster.h"

void TestScene::OnLoaded()
{
	Player*  p = (Player*)ObjectManager::GetInstance()->CreateObject<Player>();
	p->AddComponent<PKH::Cube>(L"Mesh");

	Monster* m = (Monster*)ObjectManager::GetInstance()->CreateObject<Monster>();
	m->AddComponent<PKH::Cube>(L"Mesh");


}

void TestScene::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void TestScene::Update()
{
}
