#include "stdafx.h"
#include "ChampionAI.h"
#include "MiniScorePanel.h"
#include "Champion.h"
#include "Monster.h"
#include "Minion.h"
#include "Building.h"

ChampionAI::ChampionAI(GameObject* owner)
    :IComponent(owner)
{
    unit = (Unit*)owner;
}

ChampionAI::ChampionAI(const ChampionAI& rhs)
    :IComponent(rhs)
{
}

ChampionAI::~ChampionAI()
{
}

void ChampionAI::Update()
{
    if (unit->IsDead())
    {
        deadFlag = true;
        target = nullptr;
        return;
    }
    if (deadFlag)
    {
        deadFlag = false;
        nextPoint = Vector3(-3.49f, 67.72f, 3.92f);
        wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
    }

    int minute = 0;
    int second = 0;
    MiniScorePanel::GetInstance()->GetTime(&minute, &second);

    if (minute < 1) return;
    if (minute == 1 && second == 5)
    {
        startFlag = true;
        nextPoint = Vector3(-3.49f, 67.72f, 3.92f);
        wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
        return;
    }

    if (startFlag == false) return;

    float dt = Time::DeltaTime();

    // 타겟 검색
    if (target == nullptr)
    {
        target = unit->GetLastAttacker();

        if (target == nullptr)
        {
            Unit* enemy = unit->GetNearestEnemy(unit->transform->position, 5.f);
            if (dynamic_cast<Champion*>(enemy) || dynamic_cast<Minion*>(enemy) || dynamic_cast<Building*>(enemy))
            {
                target = enemy;
            }
        }
    }
    else
    {
        if (target->IsDead())
        {
            target = nullptr;
        }
    }

    if (target != nullptr)
    {
        unit->SetAttackTarget(target);
        unit->SetNextSkill(unit->skillList[(int)SkillIndex::Attack]);
    }

    if (target != nullptr) // 타겟이 있을 때
    {
        float attackRange = unit->stat->GetValue(StatType::Range);
        Vector3 to = unit->GetAttackTarget()->transform->position - unit->transform->position;
        float dist = to.Length();
        if (dist > attackRange)
        {
            float remainDist = dist - attackRange + 0.5f;
            Vector3 point = unit->transform->position + to.Normalized() * remainDist;
            Ray ray;
            ray.origin = unit->transform->position;
            ray.direction = to.Normalized();
            RaycastHit hit;
            bool hitWall = Physics::Raycast(ray, &hit, INFINITY, LayerMask::GetMask(Layer::Wall));

            unit->agent->SetDestination(point, !hitWall);
            
        }
    }
    else //  타겟이 없을 때
    {
        Vector3 to = nextPoint - unit->transform->position;
        float dist = to.Length();
        if (dist < 3.0f)
        {
            if (wayPoint.empty() == false)
            {
                nextPoint = wayPoint.front();
                wayPoint.pop_front();
            }
        }

        moveTick += dt;
        if (moveTick > moveDelay)
        {
            moveTick = 0.f;
            unit->SetAttackTarget(nullptr);
            unit->agent->SetStoppingDistance(1.f);
            //unit->SetDestination(nextPoint);
            unit->agent->SetDestination(nextPoint, true);
        }
    }
    


}

IComponent* ChampionAI::Clone()
{
    return new ChampionAI(*this);
}
