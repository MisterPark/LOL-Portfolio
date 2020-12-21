#include "stdafx.h"
#include "NavMeshAgent.h"
#include "NavMeshMap.h"
#include "Unit.h"

PKH::NavMeshAgent::NavMeshAgent(GameObject* owner)
    :IComponent(owner)
{
    unit = dynamic_cast<Unit*>(owner);
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
            // 가야할 경로가 있다면
            if (path.empty() == false)
            {
                // nextPosition 새로 세팅
                nextPosition = path.front();
                path.erase(path.begin());
            }
            else // 최종경로에 도착했다면
            {
                isDestination = true;
                return;
            }
        }
        else // 남은 거리가 있다면
        {
            // 상태
            unit->state = UnitState::RUN;
            // 회전
            float angle = Vector3::AngleY(Vector3(0, 0, 1), direction);
            gameObject->transform->eulerAngles.y = angle;
            // 이동
            transform->position += direction * speed * TimeManager::DeltaTime();
        }
    }
}

IComponent* PKH::NavMeshAgent::Clone()
{
    return new NavMeshAgent(*this);
}

bool PKH::NavMeshAgent::SetDestination(const Vector3& target, bool noSearch)
{
    bool result = false;
    ResetPath();

    if (noSearch)
    {
        destination = target;
        path.push_back(target);
        nextPosition = target;
        isDestination = false;
    }
    else
    {
        // 길찾기 새로 수행
        result = navMeshMap->Search(transform->position, target);
        if (result == true)
        {
            // 길찾기 결과 저장
            list<PathFinder::Node*>* resultPath = navMeshMap->GetPath();
            auto iter = resultPath->begin();
            auto end = resultPath->end();
            for (; iter != end; ++iter)
            {
                path.push_back((*iter)->position);
            }
            // destination 세팅
            destination = target;
            path.push_back(target);
            // nextPosition 세팅
            nextPosition = path.front();
            path.erase(path.begin());
            isDestination = false;
        }
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
    path.clear();
    
}
