#include "stdafx.h"
#include "GameObject.h"

using namespace PKH;

PKH::GameObject::GameObject()
{
}

PKH::GameObject::~GameObject()
{
}

void PKH::GameObject::Update()
{
}

void PKH::GameObject::Render()
{
}

void PKH::GameObject::Die()
{
	isDead = true;
}

void PKH::GameObject::OnCollision(GameObject* target)
{
}

