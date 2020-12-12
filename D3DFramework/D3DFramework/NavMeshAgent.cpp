#include "stdafx.h"
#include "NavMeshAgent.h"
#include "NavMeshMap.h"

PKH::NavMeshAgent::NavMeshAgent(GameObject* owner)
    :IComponent(owner)
{
    navMeshMap = (NavMeshMap*)ObjectManager::GetInstance()->FindObject<NavMeshMap>();
}

PKH::NavMeshAgent::NavMeshAgent(const NavMeshAgent& rhs)
    :IComponent(rhs)
{
}

PKH::NavMeshAgent::~NavMeshAgent()
{
}

void PKH::NavMeshAgent::Update()
{
    if (isMoving)
    {
        if (isDestination) return;

        Vector3 remain = nextPosition - transform->position;
        Vector3 direction = remain.Normalized();
        float remainDist = remain.Length();
        // 남은 거리가 멈출 거리보다 작거나 같으면(경유지or 목적지에 도착)
        if (remainDist <= stoppingDistance)
        {
            path.pop();

            // 가야할 경로가 있다면
            if (path.empty() == false)
            {
                // nextPosition 새로 세팅
                nextPosition = path.top();
            }
            else // 최종경로에 도착했다면
            {
                isDestination = true;
                return;
            }
        }
        else // 남은 거리가 있다면
        {
            // 이동
            transform->position += direction * speed * TimeManager::DeltaTime();
        }
    }
}

IComponent* PKH::NavMeshAgent::Clone()
{
    return new NavMeshAgent(*this);
}

bool PKH::NavMeshAgent::SetDestination(const Vector3& target)
{
    // 길찾기 새로 수행
    bool result = navMeshMap->Search(transform->position, target);
    if (result == true)
    {
        ResetPath();
        // 길찾기 결과 저장
        PathFinder::Node* resNode = navMeshMap->GetResultNode();
        if (resNode == nullptr) return false;

        // destination 세팅
        destination = resNode->position;
        

        // path 세팅
        PathFinder::Node* iter = resNode;
        while (iter != nullptr)
        {
            // 도착지부터 시작지까지니까 앞에서 넣어줘서 순서를 맞춤
            path.push(iter->position);
            iter = iter->parent;
        }

        // nextPosition 세팅
        nextPosition = path.top();
        isDestination = false;
    }

    return result;
}

void PKH::NavMeshAgent::Stop()
{
    isMoving = false;
}

void PKH::NavMeshAgent::Resume()
{
    isMoving = true;
}

void PKH::NavMeshAgent::Move(const Vector3& offset)
{
}

void PKH::NavMeshAgent::ResetPath()
{
    while (!path.empty())
    {
        path.pop();
    }
    
}
