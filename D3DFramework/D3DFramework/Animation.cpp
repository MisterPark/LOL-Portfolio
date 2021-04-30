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
    
    float animSpeed = animNode.speed;
    
    //if(stopFlag == false)
    //    dmesh->PlayAnimation(animSpeed);
    dmesh->stopFlag = stopFlag;
    dmesh->animSpeed = animSpeed;
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

    int end = (int)State::END;
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
        animsets[i].speed = 1.f;
        animsets[i].name = name;
    }

    currentAnim = idleIndex;
}

string Engine::Animation::GetNameByState(int _state)
{
    string name;
    State state = (State)_state;
    switch (state)
    {
    case State::IDLE1:
        name = "idle1";
        break;
    case State::IDLE2:
        name = "idle2";
        break;
    case State::IDLE3:
        name = "idle3";
        break;
    case State::DEATH:
        name = "death";
        break;
    case State::DEATH2:
        name = "death2";
        break;
    case State::RECALL:
        name = "recall";
        break;
    case State::RECALL2:
        name = "recall2";
        break;
    case State::RECALL3:
        name = "recall3";
        break;
    case State::RUN:
        name = "run";
        break;
    case State::RUN2:
        name = "run2";
        break;
    case State::RUN_HASTE:
        name = "run_haste";
        break;
    case State::ATTACK1:
        name = "attack1";
        break;
    case State::ATTACK2:
        name = "attack2";
        break;
    case State::ATTACK3:
        name = "attack3";
        break;
    case State::ATTACK4:
        name = "attack4";
        break;
    case State::CRITICAL:
        name = "crit";
        break;
    case State::Q:
        name = "q";
        break;
    case State::W:
        name = "w";
        break;
    case State::E:
        name = "e";
        break;
    case State::R:
        name = "r";
        break;
    case State::Q2:
        name = "q2";
        break;
    case State::W2:
        name = "w2";
        break;
    case State::E2:
        name = "e2";
        break;
    case State::R2:
        name = "r2";
        break;
    case State::SPAWN:
        name = "spawn";
        break;
    default:
        name = "";
        break;
    }
    return name;
}

AnimationIndex Engine::Animation::GetIndexByState(int _state)
{
    return animsets[_state].index;
}

AnimationIndex Engine::Animation::GetCurrentAnimation()
{
    return currentAnim;
}

int Engine::Animation::GetState()
{
    return state;
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

void Engine::Animation::Reset()
{
    if (dmesh == nullptr) return;
    dmesh->ResetAnimation();
}
