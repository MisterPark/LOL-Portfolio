#include "stdafx.h"
#include "TestMan.h"
#include "StaticMesh.h"

TestMan::TestMan()
{
	transform->position = { 0,0,0 };
	StaticMesh* smesh = (StaticMesh*)AddComponent<StaticMesh>(L"StaticMesh");
	smesh->LoadMesh(L"Resource\\Mesh\\malphite\\", L"malp.X");
}

TestMan::~TestMan()
{
}

void TestMan::Initialize()
{
}

void TestMan::Release()
{
}

void TestMan::Update()
{
	GameObject::Update();
}
