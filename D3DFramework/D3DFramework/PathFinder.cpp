#include "stdafx.h"
#include "PathFinder.h"


//=======================================================
//	PathFinderNode
//=======================================================

PKH::PathFinder::Node::Node()
{
}

PKH::PathFinder::Node::Node(PathFinder::Node* parent, Vector3 position)
{
	this->parent = parent;
	this->position = position;
}

PKH::PathFinder::Node::~Node()
{
}


int PKH::PathFinder::Node::G()
{
	if (parent == nullptr) return 0;
	
	Vector3 dir = parent->position - position;
	float len = dir.Length();
	len = len + parent->G();
	return (int)len;
}

int PKH::PathFinder::Node::H(Node* dest)
{
	Vector3 dir = dest->position - position;
	float len = dir.Length();

	return (int)len;
}

int PKH::PathFinder::Node::F(Node* dest)
{
	return G() + H(dest);
}

//=======================================================
//	PathFinder
//=======================================================

PKH::PathFinder::PathFinder()
{
}

PKH::PathFinder::~PathFinder()
{
	for (auto node : nodes)
	{
		delete node.second;
	}

	nodes.clear();
}

PKH::PathFinder::Node* PKH::PathFinder::FindStartNode(const Vector3& startPos, float radius)
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

PKH::PathFinder::Node* PKH::PathFinder::FindDestinationNode(const Vector3& destPos, float radius)
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

void PKH::PathFinder::SetDestination(PKH::PathFinder::Node* dest)
{
	// nodes의 모든 노드의 도착지 변경
	for (auto node : nodes)
	{
		node.second->destination = dest;
	}
}

void PKH::PathFinder::SetPath()
{
	PathFinder::Node* iter = resultNode;
	while (iter != nullptr)
	{
		path.push_back(iter);
		iter = iter->parent;
	}
	path.reverse();
}

void PKH::PathFinder::OptimizeStartNode()
{
	// 중간경로에 시작후보가 있으면
	// 시작노드를 바꾸기
	// stack이니 역순으로 가다가 만나면 위에꺼 다날리면됨 parent = nullptr

	PKH::PathFinder::Node* iter = resultNode;
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

void PKH::PathFinder::OptimizeDestinationNode(const Vector3& destPos)
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

void PKH::PathFinder::Optimize()
{
	list<PKH::PathFinder::Node*>::iterator head1, head2, iter, end;
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

void PKH::PathFinder::AddNode(DWORD index, PKH::PathFinder::Node* pNode)
{
	nodes[index] = pNode;
}

void PKH::PathFinder::LinkNode(DWORD srcIndex, DWORD destIndex)
{
	nodes[srcIndex]->adjacency.push_back(nodes[destIndex]);
}


PathFinderType PKH::PathFinder::GetType()
{
	return type;
}

PKH::PathFinder::Node* PKH::PathFinder::GetResultNode()
{
	return resultNode;
}

list<PKH::PathFinder::Node*>* PKH::PathFinder::GetPath()
{
	return &path;
}
