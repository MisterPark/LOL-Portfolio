#include "stdafx.h"
#include "IComponent.h"
#include "Transform.h"

using namespace Engine;


Engine::IComponent::IComponent(GameObject* owner)
{
	gameObject = owner;
	if(owner != nullptr)
		transform = owner->transform;
}

Engine::IComponent::IComponent(const Engine::IComponent & rhs)
{
	
}

Engine::IComponent::~IComponent()
{
	gameObject = nullptr;
	transform = nullptr;
}

void Engine::IComponent::Update()
{
}

void Engine::IComponent::PostUpdate()
{
}
