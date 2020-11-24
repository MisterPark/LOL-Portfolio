#include "stdafx.h"
#include "TestMan.h"
#include "StaticMesh.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

TestMan::TestMan()
{
	transform->position = { 0,0,0 };
	//StaticMesh* smesh = (StaticMesh*)AddComponent<StaticMesh>(L"StaticMesh");
	//smesh->LoadMesh(L"Resource/Mesh/malphite/", L"malp.X");

	StaticMesh* smesh = RenderManager::CloneStaticMesh(L"malp");
	
	AddComponent(L"StaticMesh", smesh);
	//AddComponent<SphereCollider>(L"SphereCollider");
	AddComponent<BoxCollider>(L"BoxCollider");
	
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

void TestMan::OnCollisionEnter(const Collider* target)
{
	Collider* collider = (Collider*)GetComponent<Collider>();
	if (collider == nullptr) return;

	collider->SetColor(D3DCOLOR_ARGB(255, 255, 0, 0));
}
