#include "stdafx.h"
#include "Building.h"
#include "SphereCollider.h"
#include "GameRenderer.h"
Building::Building()
{

}

Building::~Building()
{
}

void Building::OnCollisionEnter(Collider* target)
{
	if (dynamic_cast<Unit*>(target->gameObject))
	{
		Unit* unit = (Unit*)target->gameObject;
		unit->PushedOut(this);
	}
}

