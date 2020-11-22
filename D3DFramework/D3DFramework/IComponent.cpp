#include "stdafx.h"
#include "IComponent.h"
#include "Transform.h"

using namespace PKH;


PKH::IComponent::IComponent(GameObject* owner)
{
	gameObject = owner;
	if(owner != nullptr)
		transform = owner->transform;
}

PKH::IComponent::IComponent(const PKH::IComponent & rhs)
{
	
}

PKH::IComponent::~IComponent()
{
	gameObject = nullptr;
	transform = nullptr;
}

void PKH::IComponent::Update()
{
}
