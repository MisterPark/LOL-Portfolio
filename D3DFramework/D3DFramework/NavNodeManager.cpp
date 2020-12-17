#include "stdafx.h"
#include "NavNodeManager.h"
#include "NavNode.h"
#include "SphereCollider.h"

NavNodeManager* pNavNodeManager = nullptr;
int uniqueNavNodeID = 0;

NavNodeManager::NavNodeManager()
{
}

NavNodeManager::~NavNodeManager()
{
    nodes.clear();
    selectedNodes.clear();
}

NavNodeManager* NavNodeManager::GetInstance()
{
    if (pNavNodeManager == nullptr)
    {
        pNavNodeManager = new NavNodeManager;
    }
    return pNavNodeManager;
}

void NavNodeManager::Destroy()
{
    if (pNavNodeManager)
    {
        delete pNavNodeManager;
        pNavNodeManager = nullptr;
    }
}


void NavNodeManager::Save()
{
    FileManager::MakeDirectory("Data/Nav");
    FileManager::SetDirectory("Data/Nav/Nav.dat");
    errno_t err = FileManager::OpenFile("wb");


    FileManager::WriteFile(&uniqueNavNodeID, sizeof(int), 1);

    int count = pNavNodeManager->nodes.size();
    FileManager::WriteFile(&count, sizeof(int), 1);

    for (auto node : pNavNodeManager->nodes)
    {
        FileManager::WriteFile(&node.first, sizeof(int), 1);
        FileManager::WriteFile(&node.second->transform->position.x, sizeof(float), 1);
        FileManager::WriteFile(&node.second->transform->position.y, sizeof(float), 1);
        FileManager::WriteFile(&node.second->transform->position.z, sizeof(float), 1);

        int adjCount = node.second->adjacencyArr.size();
        FileManager::WriteFile(&adjCount, sizeof(int), 1);
        for (auto adj : node.second->adjacencyArr)
        {
            FileManager::WriteFile(&adj, sizeof(int), 1);
        }
    }

    FileManager::CloseFile();
    Debug::Print("NavNode 저장");
}

void NavNodeManager::Load()
{
    FileManager::SetDirectory("Data/Nav/Nav.dat");
    FileManager::OpenFile("rb");

    int lastID = 0;
    FileManager::ReadFile(&lastID, sizeof(int), 1);
    int count = 0;
    FileManager::ReadFile(&count, sizeof(int), 1);

    for (int i = 0; i < count; i++)
    {
        NavNode* node = (NavNode*)ObjectManager::GetInstance()->CreateObject<NavNode>(Layer::Node);
        FileManager::ReadFile(&node->uniqueID, sizeof(int), 1);
        FileManager::ReadFile(&node->transform->position.x, sizeof(float), 1);
        FileManager::ReadFile(&node->transform->position.y, sizeof(float), 1);
        FileManager::ReadFile(&node->transform->position.z, sizeof(float), 1);

        int adjCount = 0;
        FileManager::ReadFile(&adjCount, sizeof(int), 1);
        for (int j = 0; j < adjCount; j++)
        {
            int adj;
            FileManager::ReadFile(&adj, sizeof(int), 1);
            node->adjacencyArr.push_back(adj);
        }

        pNavNodeManager->nodes[node->uniqueID] = node;
    }

    FileManager::CloseFile();
    
}

void NavNodeManager::LoadDebug()
{
    ClearAll();
    FileManager::SetDirectory("Data/Nav/Nav.dat");
    FileManager::OpenFile("rb");

    FileManager::ReadFile(&uniqueNavNodeID, sizeof(int), 1);
    int count = 0;
    FileManager::ReadFile(&count, sizeof(int), 1);

    for (int i = 0; i < count; i++)
    {
        NavNode* node = (NavNode*)ObjectManager::GetInstance()->CreateObject<NavNode>(Layer::Node);
        FileManager::ReadFile(&node->uniqueID, sizeof(int), 1);
        FileManager::ReadFile(&node->transform->position.x, sizeof(float), 1);
        FileManager::ReadFile(&node->transform->position.y, sizeof(float), 1);
        FileManager::ReadFile(&node->transform->position.z, sizeof(float), 1);

        int adjCount = 0;
        FileManager::ReadFile(&adjCount, sizeof(int), 1);
        for (int j = 0; j < adjCount; j++)
        {
            int adj;
            FileManager::ReadFile(&adj, sizeof(int), 1);
            node->adjacencyArr.push_back(adj);
        }

        pNavNodeManager->nodes[node->uniqueID] = node;
    }

    FileManager::CloseFile();
    Debug::Print("NavNode 불러오기");
}

void NavNodeManager::AddNode(NavNode* node)
{
    int id = uniqueNavNodeID++;
    node->uniqueID = id;
    pNavNodeManager->nodes[id] = node;
}

void NavNodeManager::DeleteNode(NavNode* node)
{
    for (auto node : pNavNodeManager->nodes)
    {
        auto iter = node.second->adjacencyArr.begin();
        auto end = node.second->adjacencyArr.end();
        for (;iter!= end;)
        {
            int id = *iter;
            if (id == node.second->uniqueID)
            {
                iter = node.second->adjacencyArr.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    pNavNodeManager->nodes.erase(node->uniqueID);
    node->Destroy();
}

void NavNodeManager::DeleteSelectedNodes()
{
    for (auto node : pNavNodeManager->selectedNodes)
    {
        DeleteNode(node);
    }
    ClearSelectedNodes();
}

NavNode* NavNodeManager::FindNode(int id)
{
    auto iter = pNavNodeManager->nodes.find(id);
    auto end = pNavNodeManager->nodes.end();
    if (iter == end)
    {
        return nullptr;
    }

    return iter->second;
}

void NavNodeManager::SelectNode(NavNode* node)
{
    node->collider->SetColor(D3DCOLOR_ARGB(255, 255, 0, 0));
    pNavNodeManager->selectedNodes.push_back(node);
}

void NavNodeManager::LinkNode()
{
    for (auto src : pNavNodeManager->selectedNodes)
    {
        for (auto dest : pNavNodeManager->selectedNodes)
        {
            if (src == dest)continue;

            bool alreadyExist = false;
            for (auto iter : src->adjacencyArr)
            {
                if (iter == dest->uniqueID)
                {
                    alreadyExist = true;
                    break;
                }
            }

            if(alreadyExist == false)
                src->adjacencyArr.push_back(dest->uniqueID);
        }
        
    }
}

void NavNodeManager::ClearSelectedNodes()
{
    for (auto node : pNavNodeManager->selectedNodes)
    {
        node->collider->SetColor(D3DCOLOR_ARGB(255, 0, 255, 0));
    }
    pNavNodeManager->selectedNodes.clear();
}

void NavNodeManager::ClearAll()
{
    for (auto node : pNavNodeManager->nodes)
    {
        node.second->Destroy();
    }
    pNavNodeManager->nodes.clear();
    pNavNodeManager->selectedNodes.clear();
    uniqueNavNodeID = 0;
}
