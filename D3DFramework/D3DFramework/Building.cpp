#include "stdafx.h"
#include "Building.h"
#include "SphereCollider.h"
#include "TurretFloatingBar.h"

Building::Building()
{
	bar = (TurretFloatingBar*)SceneManager::GetCurrentScene()->CreateObject<TurretFloatingBar>(Layer::UI);
	bar->SetTarget(this);
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

void Building::OnDamaged(Unit* target, Skill* targetSkill, float* damage)
{
	bool invinCheck = false;

	for (auto& building : frontBuildingList)
	{
		if (building->IsDead()) {
			invinCheck = false;
			break;
		}
		else
			invinCheck = true;
	}
	

	if (invinCheck)
		*damage = 0.f;
}

