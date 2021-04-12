#include "stdafx.h"
#include "Aura.h"
#include "Effect_Red_Buff.h"
#include "Effect_Blue_Buff.h"
#include "Effect_Baron_Buff.h"

Aura::Aura(GameObject* owner)
    :IComponent(owner)
{
    redBuff = (Effect_Red_Buff*)SceneManager::GetCurrentScene()->CreateObject< Effect_Red_Buff>(Layer::Effect);
    redBuff->Hide();
    blueBuff = (Effect_Blue_Buff*)SceneManager::GetCurrentScene()->CreateObject< Effect_Blue_Buff>(Layer::Effect);
    blueBuff->Hide();
    baronBuff = (Effect_Baron_Buff*)SceneManager::GetCurrentScene()->CreateObject< Effect_Baron_Buff>(Layer::Effect);
    baronBuff->Hide();
}

Aura::Aura(const Aura& rhs)
    :IComponent(rhs)
{
}

Aura::~Aura()
{
    redBuff = nullptr;
    blueBuff = nullptr;
    baronBuff = nullptr;
}

void Aura::PostUpdate()
{
    angle += 1.f * Time::DeltaTime();
    angle = fmodf(angle, 360.f);
    redBuff->transform->eulerAngles.y = angle;
    blueBuff->transform->eulerAngles.y = angle;
    baronBuff->transform->eulerAngles.y = angle;

    if (gameObject != nullptr)
    {
        redBuff->transform->position = gameObject->transform->position;
        redBuff->transform->position.y += 0.1f;
        blueBuff->transform->position = gameObject->transform->position;
        blueBuff->transform->position.y += 0.1f;
        baronBuff->transform->position = gameObject->transform->position;
        baronBuff->transform->position.y += 0.1f;
    }
}

IComponent* Aura::Clone()
{
    return nullptr;
}

void Aura::ShowRedBuff(bool _show)
{
    redBuff->Show(_show);
}

void Aura::ShowBlueBuff(bool _show)
{
    blueBuff->Show(_show);
}

void Aura::ShowBaronBuff(bool _show)
{
    baronBuff->Show(_show);
}
