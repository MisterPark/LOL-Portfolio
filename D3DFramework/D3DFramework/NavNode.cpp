#include "stdafx.h"
#include "NavNode.h"
#include "SphereCollider.h"

NavNode::NavNode()
{
	collider = (SphereCollider*)AddComponent<SphereCollider>(L"SphereCollider");
	collider->radius = 0.5f;
}

NavNode::~NavNode()
{
	collider = nullptr;
}

void NavNode::Initialize()
{
}

void NavNode::Release()
{
}

void NavNode::Update()
{
	GameObject::Update();
}

void NavNode::PostRender()
{
	GameObject::PostRender();
	
	for (int adj : adjacencyArr)
	{
		NavNode* adjNode = NavNodeManager::FindNode(adj);
		if (adjNode == nullptr) continue;

		RenderManager::DrawLine(transform->position, adjNode->transform->position, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
}

void NavNode::OnCollisionEnter(const Collider* target)
{
}
