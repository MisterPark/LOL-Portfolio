#include "stdafx.h"
#include "Animation.h"

PKH::Animation::Animation(GameObject* owner)
    :IComponent(owner)
{
}

PKH::Animation::Animation(const Animation& rhs)
    :IComponent(rhs)
{
}

PKH::Animation::~Animation()
{
}

void PKH::Animation::Update()
{
}

IComponent* PKH::Animation::Clone()
{
    return nullptr;
}
