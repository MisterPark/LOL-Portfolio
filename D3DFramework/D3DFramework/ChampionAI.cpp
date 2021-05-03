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

    // 웨이포인트 세팅
    wayPoints[(int)Lane::BlueTop].push_back(Vector3(-30.88f, 67.71f, 40.80f));
    wayPoints[(int)Lane::BlueTop].push_back(Vector3(-42.32f, 67.71f, 28.58f));
    wayPoints[(int)Lane::BlueTop].push_back(Vector3(-42.87f, 68.01f, -36.16f));

    wayPoints[(int)Lane::BlueMid].push_back(Vector3(-3.49f, 67.72f, 3.92f));
    wayPoints[(int)Lane::BlueMid].push_back(Vector3(-42.87f, 68.01f, -36.16f));

    wayPoints[(int)Lane::BlueBot].push_back(Vector3(34.58f, 67.71f, -23.79f));
    wayPoints[(int)Lane::BlueBot].push_back(Vector3(23.98f, 67.71f, -34.88f));
    wayPoints[(int)Lane::BlueBot].push_back(Vector3(-42.87f, 68.01f, -36.16f));

    wayPoints[(int)Lane::RedTop].push_back(Vector3(-42.32f, 67.71f, 28.58f));
    wayPoints[(int)Lane::RedTop].push_back(Vector3(-30.88f, 67.71f, 40.80f));
    wayPoints[(int)Lane::RedTop].push_back(Vector3(36.59f, 68.05f, 42.96f));

    wayPoints[(int)Lane::RedMid].push_back(Vector3(-3.49f, 67.72f, 3.92f));
    wayPoints[(int)Lane::RedMid].push_back(Vector3(36.59f, 68.05f, 42.96f));

    wayPoints[(int)Lane::RedBot].push_back(Vector3(23.98f, 67.71f, -34.88f));
    wayPoints[(int)Lane::RedBot].push_back(Vector3(34.58f, 67.71f, -23.79f));
    wayPoints[(int)Lane::RedBot].push_back(Vector3(36.59f, 68.05f, 42.96f));
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
        return;
    }
    if (deadFlag)
    {
        deadFlag = false;
        wayPoint.clear();
        auto& laneWayPointList = wayPoints[(int)lane];
        for (auto& way : laneWayPointList)
        {
            wayPoint.push_back(way);
        }
        nextPoint = wayPoint.front();
        wayPoint.pop_front();
        //nextPoint = Vector3(-3.49f, 67.72f, 3.92f);
        //wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
    }

    int minute = 0;
    int second = 0;
    MiniScorePanel::GetInstance()->GetTime(&minute, &second);

    if (minute < 1) return;
    if (minute == 1 && second == 5)
    {
        startFlag = true;
        wayPoint.clear();
        auto& laneWayPointList = wayPoints[(int)lane];
        for (auto& way : laneWayPointList)
        {
            wayPoint.push_back(way);
        }
        nextPoint = wayPoint.front();
        wayPoint.pop_front();
        /*nextPoint = Vector3(-3.49f, 67.72f, 3.92f);
        wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));*/
        return;
    }

    if (startFlag == false) return;

    float dt = Time::DeltaTime();

    // 타겟 검색
    //if (unit->GetAttackTarget() == nullptr)
    //{
    //    unit->SetAttackTarget(unit->GetNearestEnemy(unit->transform->position, 5.5f));

    //    if (unit->GetAttackTarget() == nullptr)
    //    {
    //        
    //        unit->SetAttackTarget(unit->GetLastAttacker());
    //    }
    //}
    if (unit->GetAttackTarget() == nullptr)
    {
        unit->SetAttackTarget(unit->GetLastAttacker());

        if (unit->GetAttackTarget() == nullptr)
        {
            float range = unit->stat->GetValue(StatType::Range) - 0.5f;
            unit->SetAttackTarget(unit->GetNearestEnemy(unit->transform->position, range));
            unit->SetNextSkill(unit->skillList[(int)SkillIndex::Attack]);
        }
    }
    

    if (unit->GetAttackTarget() != nullptr) // 타겟이 있을 때
    {
        chaseTick += dt;

        if (unit->GetAttackTarget()->IsDead())
        {
            unit->SetAttackTarget(nullptr);
            unit->SetNextSkill(unit->skillList[(int)SkillIndex::Attack]);
            return;
        }

        float attackRange = unit->stat->GetValue(StatType::Range);
        float detectRange = attackRange + 4.f;
        Vector3 to = unit->GetAttackTarget()->transform->position - unit->transform->position;
        float dist = to.Length();
        if (dist < detectRange)
        {
            if (dist < attackRange)
            {
                if (chaseTick > chaseDelay)
                {
                    chaseTick = 0.f;

                    unit->SetAttackTarget(nullptr);
                    float remainDist = dist - attackRange + 1.f;
                    Vector3 point = unit->transform->position + to.Normalized() * remainDist;
                    unit->Move(1.f, point);
                }
            }
            
        }
        else
        {
            unit->SetAttackTarget(nullptr);
            chaseTick = 0.f;
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
            unit->Move(1.f, nextPoint);
        }
    }
    


}

IComponent* ChampionAI::Clone()
{
    return new ChampionAI(*this);
}

void ChampionAI::SetLane(Lane _lane)
{
    this->lane = _lane;
}
