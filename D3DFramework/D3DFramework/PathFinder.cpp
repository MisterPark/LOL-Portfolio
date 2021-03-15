#include "stdafx.h"
#include "PathFinder.h"


//=======================================================
//	PathFinderNode
//=======================================================

Engine::PathFinder::Node::Node()
{
}

Engine::PathFinder::Node::Node(PathFinder::Node* parent, Vector3 position)
{
	this->parent = parent;
	this->position = position;
}

Engine::PathFinder::Node::~Node()
{
}


int Engine::PathFinder::Node::G()
{
	if (parent == nullptr) return 0;
	
	Vector3 dir = parent->position - position;
	float len = dir.Length();
	len = len + parent->G();
	return (int)len;
}

int Engine::PathFinder::Node::H()
{
	if (destination == nullptr) return 0;
	Vector3 dir = destination->position - position;
	float len = dir.Length();

	return (int)len;
}

int Engine::PathFinder::Node::F()
{
	return G() + H();
}

//=======================================================
//	PathFinder
//=======================================================

Engine::PathFinder::PathFinder()
{
}

Engine::PathFinder::~PathFinder()
{
	for (auto node : nodes)
	{
		delete node.second;
	}

	nodes.clear();
}

Engine::PathFinder::Node* Engine::PathFinder::FindStartNode(const Vector3& startPos, float radius)
{
	// nodes 중에서 startPos와 가장 가까운 포지션의 노드 찾기
	//  +  인접노드리스트도 추가
	candidatesStart.clear();

	PathFinder::Node* result = nullptr;

	int mask = LayerMask::GetMask(Layer::Wall);

	// nodes 중에서
	for (auto node : nodes)
	{
		Vector3 to = node.second->position - startPos;
		Ray ray;
		ray.origin = startPos;
		ray.direction = to.Normalized();
		float dist = to.Length();
		// 거리가 기준반경 안에 없으면 continue;
		if (dist > radius) continue;

		// 시작지점과 노드사이에 벽이 있으면 continue;
		RaycastHit hit;
		if (Physics::Raycast(ray, &hit, dist, mask)) continue;

		// 기준반경 안에 있으면서, 사이에 벽이 없는 노드.
		int id = (int)(dist * 100); // 정밀도를 위한 곱셈
		candidatesStart[id]= node.second;
	}

	if (candidatesStart.size() > 0)
	{
		result = candidatesStart.begin()->second;
	}
	return result;
}

Engine::PathFinder::Node* Engine::PathFinder::FindDestinationNode(const Vector3& destPos, float radius)
{
	candidatesDest.clear();

	PathFinder::Node* result = nullptr;

	int mask = LayerMask::GetMask(Layer::Wall);

	// nodes 중에서
	for (auto node : nodes)
	{
		Vector3 to = node.second->position - destPos;
		Ray ray;
		ray.origin = destPos;
		ray.direction = to.Normalized();
		float dist = to.Length();
		// 거리가 기준반경 안에 없으면 continue;
		if (dist > radius) continue;

		// 시작지점과 노드사이에 벽이 있으면 continue;
		RaycastHit hit;
		if (Physics::Raycast(ray, &hit, dist, mask)) continue;

		// 기준반경 안에 있으면서, 사이에 벽이 없는 노드.
		int id = (int)(dist * 100); // 정밀도를 위한 곱셈
		candidatesDest[id] = node.second;
	}

	if (candidatesDest.size() > 0)
	{
		result = candidatesDest.begin()->second;
	}
	return result;
}

void Engine::PathFinder::SetDestination(Engine::PathFinder::Node* dest)
{
	// nodes의 모든 노드의 도착지 변경
	for (auto node : nodes)
	{
		node.second->destination = dest;
	}
}

void Engine::PathFinder::SetPath()
{
	PathFinder::Node* iter = resultNode;
	while (iter != nullptr)
	{
		path.push_back(iter);
		iter = iter->parent;
	}
	path.reverse();
}

void Engine::PathFinder::OptimizeStartNode()
{
	// 중간경로에 시작후보가 있으면
	// 시작노드를 바꾸기
	// stack이니 역순으로 가다가 만나면 위에꺼 다날리면됨 parent = nullptr

	Engine::PathFinder::Node* iter = resultNode;
	while (iter != nullptr)
	{
		for (auto candidate : candidatesStart)
		{
			if (candidate.second == iter)
			{
				iter->parent = nullptr;
				return;
			}
		}

		iter = iter->parent;
	}


}

void Engine::PathFinder::OptimizeDestinationNode(const Vector3& destPos)
{
	auto iter = path.begin();
	auto end = path.end();
	bool isFound = false;

	for (; iter != end; ++iter)
	{
		if (isFound) break;
		for (auto node : candidatesDest)
		{
			if (node.second == (*iter))
			{
				isFound = true;
				break;
			}
		}
	}

	for (; iter != end;)
	{
		iter = path.erase(iter);
	}


}

void Engine::PathFinder::Optimize()
{
	list<Engine::PathFinder::Node*>::iterator head1, head2, iter, end;
	int mask = LayerMask::GetMask(Layer::Wall);

	iter = path.begin();
	end = path.end();
	
	for (; iter != end; ++iter)
	{
		head1 = iter;
		head1++;
		if (head1 == end) return;

		for (head2 = head1; head2 != end; ++head2)
		{
			Ray ray;
			ray.origin = (*iter)->position;
			ray.origin.y += 0.5f;
			Vector3 to = (*head2)->position;
			to.y += 0.5f;
			to -= ray.origin;
			ray.direction = to.Normalized();
			float dist = to.Length();
			RaycastHit hit;
			if (Physics::Raycast(ray, &hit, dist, mask))
			{
				continue;
			}

			while (head1 != head2)
			{
				head1 = path.erase(head1);
			}
			
		}
		
		
	}
}

void Engine::PathFinder::AddNode(DWORD index, Engine::PathFinder::Node* pNode)
{
	nodes[index] = pNode;
}

void Engine::PathFinder::LinkNode(DWORD srcIndex, DWORD destIndex)
{
	nodes[srcIndex]->adjacency.push_back(nodes[destIndex]);
}


PathFinderType Engine::PathFinder::GetType()
{
	return type;
}

Engine::PathFinder::Node* Engine::PathFinder::GetResultNode()
{
	return resultNode;
}

list<Engine::PathFinder::Node*>* Engine::PathFinder::GetPath()
{
	return &path;
}
