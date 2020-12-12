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
    
    // ���¸���Ʈ
    priority_queue<Node*, vector<Node*>, ComparePFNode> openList;
    set<Node*> closeList;
    // ���� ��� ����
    PathFinder::Node* sNode = FindStartNode(start);
    if (sNode == nullptr) return false;
    sNode->parent = nullptr;
    openList.push(sNode);
    
    // ������ ����
    PathFinder::Node* eNode = FindDestinationNode(dest);
    if (eNode == nullptr) return false;
    eNode->parent = nullptr;
    // ���� ��� �ʱ�ȭ
    resultNode = eNode;

    SetDestination(eNode);

    while (!openList.empty())
    {
        // OpenList���� �ϳ� �̰� (������ F�� �۱� ������ ��ó���� ������ ��)
        PathFinder::Node* current = openList.top();
        openList.pop();

        // ���� ��尡 ���� ��尡 ������ return ture;
        if (current == eNode)
        {
            return true;
        }

        // �ƴϸ� CloseList�� �߰�
        closeList.insert(current);

        // ��� ���� ����� ���� ������ OpenList�� �߰�(CloseList�� �̹� �ִٸ� �߰� ����)
        for (auto adjNode : current->adjacency)
        {
            auto end = closeList.end();
            auto find = closeList.find(adjNode);
            if (find == end)
            {
                // Close List�� ������尡 ������ Open List�� �߰�
                adjNode->parent = current;
                openList.push(adjNode);
            }
             
        }


    }



    return false;
}