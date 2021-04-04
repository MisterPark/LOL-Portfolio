#include "stdafx.h"
#include "MinionAI.h"
#include "Unit.h"

MinionAI::MinionAI(GameObject* owner)
    :IComponent(owner)
{
    net = Network::GetInstance();
    unit = (Unit*)owner;
}

MinionAI::MinionAI(const MinionAI& rhs)
    :IComponent(rhs)
{
}

MinionAI::~MinionAI()
{
    unit = nullptr;
    target = nullptr;
}

void MinionAI::Update()
{
    if (unit->IsDead())
    {
        return;
    }
    float dt = Time::DeltaTime();

    if (unit->GetAttackTarget() == nullptr)
    {
        unit->SetAttackTarget(unit->GetLastAttacker());

        if (unit->GetAttackTarget() == nullptr)
        {
            unit->SetAttackTarget(unit->GetNearestEnemy(unit->transform->position, 3.5f));
            unit->SetNextSkill(unit->skillList[(int)SkillIndex::Attack]);
        }
    }

    if (unit->GetAttackTarget() != nullptr) // 타겟이 있을 때
    {
        if (unit->GetAttackTarget()->IsDead())
        {
            unit->SetAttackTarget(nullptr);
            return;
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
            unit->agent->SetStoppingDistance(0.05f);
            //unit->SetDestination(nextPoint);
            unit->agent->SetDestination(nextPoint, true);
        }
    }
}

IComponent* MinionAI::Clone()
{
    return new MinionAI(*this);
}

void MinionAI::SetTarget(Unit* _target)
{
    target = _target;
}
