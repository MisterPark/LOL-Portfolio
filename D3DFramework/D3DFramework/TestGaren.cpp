#include "stdafx.h"
#include "TestGaren.h"

TestGaren::TestGaren()
{
	transform->position = { 0,0,0 };
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"garen");
	AddComponent(L"DynamicMesh", dmesh);
}

TestGaren::~TestGaren()
{
}

void TestGaren::Initialize()
{
}

void TestGaren::Release()
{
}

void TestGaren::Update()
{
	if (InputManager::GetMouseLButtonDown())
	{
		currentAnimKey++;
	}

	DynamicMesh* dmesh = (DynamicMesh*)GetComponent(L"DynamicMesh");
	if (dmesh != nullptr)
	{
		dmesh->SetAnimationSet(currentAnimKey);
		dmesh->PlayAnimation(TimeManager::DeltaTime());
	}
	GameObject::Update();

	transform->Update();
}
