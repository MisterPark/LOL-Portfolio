#include "stdafx.h"
#include "CubeMan.h"
#include "Cube.h"
#include "Player.h"

PKH::CubeMan::CubeMan()
{
	
	AddComponent<Cube>(L"Mesh");
}

PKH::CubeMan::~CubeMan()
{
}

void PKH::CubeMan::Update()
{
	GameObject* obj = ObjectManager::GetInstance()->FindObject<Player>();
	Mesh* mesh = (Mesh*)obj->GetComponent(L"Mesh");
	VertexColor* vertices;
	mesh->GetVertexBuffer()->Lock(0, 0, (void**)&vertices, 0);

	

	mesh->GetVertexBuffer()->Unlock();
}
