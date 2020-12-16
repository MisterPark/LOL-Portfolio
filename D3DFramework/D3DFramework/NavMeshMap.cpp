#include "stdafx.h"
#include "NavMeshMap.h"
#include "MeshCollider.h"

using namespace PKH;

PKH::NavMeshMap::NavMeshMap()
{
	isVisible = false;
	transform->scale = { 0.1f,0.1f, 0.1f };
	transform->Update();

	//transform->eulerAngles.y = D3DXToRadian(180.f);
	navMesh = RenderManager::CloneNavMesh(L"summoner_rift_nav");
	AddComponent(L"NavMesh", navMesh);
	AddComponent<MeshCollider>(L"MeshCollider");

	pPathFinder = new Astar();
	SetNavigationInfo();
}

PKH::NavMeshMap::~NavMeshMap()
{
	delete pPathFinder;
	pPathFinder = nullptr;
}

void PKH::NavMeshMap::Initialize()
{
}

void PKH::NavMeshMap::Release()
{
}

void PKH::NavMeshMap::Update()
{
	GameObject::Update();

	if (InputManager::GetKeyDown('P'))
	{
		isVisible = !isVisible;
	}
}

void PKH::NavMeshMap::SetNavigationInfo()
{
	DWORD triangleCount = navMesh->GetFaceCount();
	Vector3* pVertices = navMesh->GetVertices();
	DWORD* pIndices = navMesh->GetIndices();
	AdjacencyInfo* pAdjacencyInfo = navMesh->GetAdjacencyInfo();
	// TODO : ★★★★★여기서부터 해야함
	// 인접 삼각형 정보를 통해서
	// 삼각형의 중점
	// 
	for (int i = 0; i < triangleCount; i++)
	{
		DWORD index = i * 3;
		Vector3 a = pVertices[pIndices[index]];
		Vector3 b = pVertices[pIndices[index + 1]];
		Vector3 c = pVertices[pIndices[index + 2]];

		
		// 무게 중심
		Vector3 barycentricCoord;
		barycentricCoord = a + b + c;
		barycentricCoord.x /= 3.f;
		barycentricCoord.y /= 3.f;
		barycentricCoord.z /= 3.f;

		//월드로 바꿔야 함
		D3DXVec3TransformCoord(&barycentricCoord, &barycentricCoord, &transform->world);

		PathFinder::Node* node = new PathFinder::Node();
		node->position = barycentricCoord;
		pPathFinder->AddNode(node);
	}

	for (int i = 0; i < triangleCount; i++)
	{
		if (pAdjacencyInfo[i].a != ULONG_MAX)
			pPathFinder->LinkNode(i, pAdjacencyInfo[i].a);
		if (pAdjacencyInfo[i].b != ULONG_MAX)
			pPathFinder->LinkNode(i, pAdjacencyInfo[i].b);
		if (pAdjacencyInfo[i].c != ULONG_MAX)
			pPathFinder->LinkNode(i, pAdjacencyInfo[i].c);

	}
	
}

bool PKH::NavMeshMap::Search(const Vector3& start, const Vector3& dest)
{
	return pPathFinder->Search(start, dest);
}

PathFinder::Node* PKH::NavMeshMap::GetResultNode()
{
	return pPathFinder->GetResultNode();
}
