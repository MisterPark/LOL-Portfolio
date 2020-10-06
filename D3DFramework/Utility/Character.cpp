#include "stdafx.h"
#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::Update()
{
	
	for (auto& comp : components)
	{
		comp.second->Update();
	}
}
