#include "stdafx.h"
#include "TestGaren.h"
#include "SphereCollider.h"
#include "NavMeshAgent.h"

TestGaren::TestGaren()
{
	transform->position = { 0,0,0 };
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"garen");
	AddComponent(L"DynamicMesh", dmesh);

	SphereCollider* collider = (SphereCollider*)AddComponent<SphereCollider>(L"SphereCollider");
	collider->radius = 1.5f;
	collider->center = { 0,1.f,0 };

	AddComponent< NavMeshAgent>(L"NavMeshAgent");
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
	//transform->Update();
	GameObject::Update();

	
}
