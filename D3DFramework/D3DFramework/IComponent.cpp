#include "stdafx.h"
#include "IComponent.h"
#include "Transform.h"

using namespace PKH;

PKH::IComponent::IComponent()
{
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
