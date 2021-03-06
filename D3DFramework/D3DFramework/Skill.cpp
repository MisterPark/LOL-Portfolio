#include "stdafx.h"
#include "Skill.h"
#include "Unit.h"

Skill::Skill()
{
}

Skill::~Skill()
{
	
}

bool Skill::IsAvailable()
{
	if (!active)
		return true;
	return false;
}

