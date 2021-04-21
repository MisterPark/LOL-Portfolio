#include "stdafx.h"
#include "ScuttleracerAI.h"
#include "Unit.h"

ScuttleracerAI::ScuttleracerAI(GameObject* owner)
    :IComponent(owner)
{
    unit = (Unit*)owner;

}

ScuttleracerAI::ScuttleracerAI(const ScuttleracerAI& rhs)
    :IComponent(rhs)
{
}

ScuttleracerAI::~ScuttleracerAI()
{
    unit = nullptr;
}

void ScuttleracerAI::Update()
{
    if (unit->IsDead())
    {
        return;
    }
    else
    {
        float dt = Time::DeltaTime();

        Vector3 to = nextPoint - unit->transform->position;
        float dist = to.Length();
        if (dist < 3.f)
        {
            if (wayPoint.empty() == false)
            {
                nextPoint = wayPoint.front();
                wayPoint.pop_front();
                wayPoint.emplace_back(nextPoint);
            }
        }

        moveTick += dt;
        if (moveTick > moveDelay)
        {
            moveTick = 0.f;
            unit->agent->SetStoppingDistance(0.01f);
            unit->agent->SetDestination(nextPoint, true);
            //Vector3 point = wayPoint.front();
            //nextPoint = point;
            //wayPoint.pop_front();
            ///wayPoint.emplace_back(point);
        }
    }


}

IComponent* ScuttleracerAI::Clone()
{
    return new ScuttleracerAI(*this);
}

