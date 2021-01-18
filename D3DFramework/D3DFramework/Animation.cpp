#include "stdafx.h"
#include "Animation.h"
#include "Unit.h"

PKH::Animation::Animation(GameObject* owner)
    :IComponent(owner)
{
    unit = dynamic_cast<Unit*>(owner);
    
}

PKH::Animation::Animation(const Animation& rhs)
    :IComponent(rhs)
{
}

PKH::Animation::~Animation()
{
    animsets.clear();
}

void PKH::Animation::PostUpdate()
{
    if (unit == nullptr) return;
    if (dmesh == nullptr) return;

    float dt = TimeManager::DeltaTime();

    currentAnim = animsets[(int)unit->state].index;
    dmesh->SetAnimationSet(currentAnim);
    
    if (dmesh->IsAnimationSetEnd())
    {
        if (animsets[currentAnim].isLoop == false)
        {
            currentAnim = animsets[(int)UnitState::IDLE1].index;
        }
    }
    
    float animSpeed = dt * animsets[(int)unit->state].period * animsets[(int)unit->state].speed;
    
    dmesh->PlayAnimation(animSpeed);
}

IComponent* PKH::Animation::Clone()
{
    return new Animation(*this);
}

void PKH::Animation::AttachToDynamicMesh(DynamicMesh* _dmesh)
{
    this->dmesh = _dmesh;

    UINT idleIndex = 0;
    dmesh->GetAnimationIndex(&idleIndex, "idle1");

    int end = (int)UnitState::END;
    for (int i = 0; i < end; i++)
    {
        UINT idx = 0;
        string name = GetNameByState((UnitState)i);
        if (dmesh->GetAnimationIndex(&idx, name.c_str()))
        {
            animsets[i].index = idx;
            animsets[i].period = dmesh->GetPeriod(idx);
        }
        else
        {
            animsets[i].index = idleIndex;
            animsets[i].period = dmesh->GetPeriod(idleIndex);
        }
        animsets[i].speed = 1.f / animsets[i].period;
        animsets[i].name = name;
    }

    currentAnim = idleIndex;
}

string PKH::Animation::GetNameByState(UnitState state)
{
    string name;
    switch (state)
    {
    case UnitState::IDLE1:
        name = "idle1";
        break;
    case UnitState::IDLE2:
        name = "idle2";
        break;
    case UnitState::IDLE3:
        name = "idle3";
        break;
    case UnitState::DEATH:
        name = "death";
        break;
    case UnitState::RECALL:
        name = "recall";
        break;
    case UnitState::RECALL2:
        name = "recall2";
        break;
    case UnitState::RECALL3:
        name = "recall3";
        break;
    case UnitState::RUN:
        name = "run";
        break;
    case UnitState::RUN2:
        name = "run2";
        break;
    case UnitState::RUN_HASTE:
        name = "run_haste";
        break;
    case UnitState::ATTACK1:
        name = "attack1";
        break;
    case UnitState::ATTACK2:
        name = "attack2";
        break;
    case UnitState::ATTACK3:
        name = "attack3";
        break;
    case UnitState::ATTACK4:
        name = "attack4";
        break;
    case UnitState::CRITICAL:
        name = "crit";
        break;
    case UnitState::Q:
        name = "q";
        break;
    case UnitState::W:
        name = "w";
        break;
    case UnitState::E:
        name = "e";
        break;
    case UnitState::R:
        name = "r";
        break;
    case UnitState::Q2:
        name = "q2";
        break;
    case UnitState::W2:
        name = "w2";
        break;
    case UnitState::E2:
        name = "e2";
        break;
    case UnitState::R2:
        name = "r2";
        break;
    case UnitState::SPAWN:
        name = "spawn";
        break;
    default:
        name = "";
        break;
    }
    return name;
}

void PKH::Animation::SetLoop(UnitState state, bool loop)
{
    animsets[(int)state].isLoop = loop;
}

void PKH::Animation::SetSpeed(UnitState state, float speed)
{
    animsets[(int)state].speed = speed;
}

bool PKH::Animation::IsFrameEnd()
{
    if (dmesh == nullptr) return false;
    return dmesh->IsAnimationSetEnd();
}
