#include "stdafx.h"
#include "Animation.h"
#include "Unit.h"

Engine::Animation::Animation(GameObject* owner)
    :IComponent(owner)
{
    
}

Engine::Animation::Animation(const Animation& rhs)
    :IComponent(rhs)
{
}

Engine::Animation::~Animation()
{
    animsets.clear();
}

void Engine::Animation::PostUpdate()
{
    if (dmesh == nullptr) return;

    float dt = Time::DeltaTime();

    Animation::Node animNode = animsets[state];
    currentAnim = animNode.index;
    dmesh->SetAnimationSet(currentAnim);
    
    if (dmesh->IsAnimationSetEnd())
    {
        if (animNode.isLoop == false)
        {
            state = 0;
            animNode = animsets[0];
            currentAnim = animsets[0].index;
        }
    }
    
    float animSpeed = animNode.period * animNode.speed * dt;
    
    //if(stopFlag == false)
    //    dmesh->PlayAnimation(animSpeed);
    dmesh->stopFlag = stopFlag;
    dmesh->animSpeed += animSpeed;
}

IComponent* Engine::Animation::Clone()
{
    return new Animation(*this);
}

void Engine::Animation::AttachToDynamicMesh(DynamicMesh* _dmesh)
{
    this->dmesh = _dmesh;

    UINT idleIndex = 0;
    dmesh->GetAnimationIndex(&idleIndex, "idle1");

    int end = (int)UnitState::END;
    for (int i = 0; i < end; i++)
    {
        UINT idx = 0;
        string name = GetNameByState(i);
        if (dmesh->GetAnimationIndex(&idx, name.c_str()))
        {
            animsets[i].index = idx;
            animsets[i].period = (float)dmesh->GetPeriod(idx);
        }
        else
        {
            animsets[i].index = idleIndex;
            animsets[i].period = (float)dmesh->GetPeriod(idleIndex);
        }
        animsets[i].speed = 1.f / animsets[i].period;
        animsets[i].name = name;
    }

    currentAnim = idleIndex;
}

string Engine::Animation::GetNameByState(int _state)
{
    string name;
    UnitState unitState = (UnitState)_state;
    switch (unitState)
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
    case UnitState::DEATH2:
        name = "death2";
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

UINT Engine::Animation::GetIndexByState(int _state)
{
    return animsets[_state].index;
}

UINT Engine::Animation::GetCurrentAnimation()
{
    return currentAnim;
}

void Engine::Animation::SetState(int _state)
{
    state = _state;
}

void Engine::Animation::SetLoop(int _state, bool loop)
{
    animsets[_state].isLoop = loop;
}

void Engine::Animation::SetSpeed(int _state, float speed)
{
    animsets[_state].speed = speed;
}

bool Engine::Animation::IsFrameEnd()
{
    if (dmesh == nullptr) return false;
    return dmesh->IsAnimationSetEnd();
}

void Engine::Animation::Stop()
{
    stopFlag = true;
}

void Engine::Animation::Resume()
{
    stopFlag = false;
}
