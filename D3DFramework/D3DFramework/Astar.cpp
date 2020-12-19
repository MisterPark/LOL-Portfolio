#include "stdafx.h"
#include "Astar.h"

using namespace PKH;

PKH::Astar::Astar()
{
    type = PathFinderType::Astar;
}

PKH::Astar::~Astar()
{
}

bool PKH::Astar::Search(const Vector3& start, const Vector3& dest)
{
    path.clear();
    // 오픈리스트
    priority_queue<Node*, vector<Node*>, ComparePFNode> openList;
    set<Node*> closeList;
    // 시작 노드 세팅
    PathFinder::Node* sNode = FindStartNode(start);
    if (sNode == nullptr) return false;
    sNode->parent = nullptr;
    openList.push(sNode);
    
    // 도착지 세팅
    PathFinder::Node* eNode = FindDestinationNode(dest);
    if (eNode == nullptr) return false;
    eNode->parent = nullptr;
    // 이전 결과 초기화
    resultNode = eNode;

    SetDestination(eNode);

    while (!openList.empty())
    {
        // OpenList에서 하나 뽑고 (무조건 F가 작기 때문에 맨처음꺼 뽑으면 됨)
        PathFinder::Node* current = openList.top();
        openList.pop();

        // 현재 노드가 도착 노드가 맞으면 return true;
        if (current == eNode)
        {
            // 끝내기 전에 중간경로에 시작 후보가 있는지 확인
            OptimizeStartNode();
            
            SetPath();
            OptimizeDestinationNode(dest);
            Optimize();

            return true;
        }

        // 아니면 CloseList에 추가
        closeList.insert(current);

        // 방금 뽑은 노드의 인접 노드들을 OpenList에 추가(CloseList에 이미 있다면 추가 안함)
        for (auto adjNode : current->adjacency)
        {
            auto end = closeList.end();
            auto find = closeList.find(adjNode);
            if (find == end)
            {
                // Close List에 인접노드가 없으면 Open List에 추가
                adjNode->parent = current;
                openList.push(adjNode);
            }
            
            // 인접노드중에 도착노드가 있다면?
        }


    }



    return false;
}
