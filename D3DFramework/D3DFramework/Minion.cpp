#include "stdafx.h"
#include "Minion.h"
#include "MinionFloatingBar.h"
#include "MinionAI.h"
#include "SphereCollider.h"

Minion::Minion()
{
	bar = (MinionFloatingBar*)SceneManager::GetCurrentScene()->CreateObject<MinionFloatingBar>(Layer::UI);
	bar->SetTarget(this);

	ai =(MinionAI*)AddComponent<MinionAI>(L"AI");
}

Minion::~Minion()
{
	bar = nullptr;
	ai = nullptr;
}

void Minion::OnCollisionEnter(Collider* target)
{
	if (dynamic_cast<Unit*>(target->gameObject))
	{
		Unit* unit = (Unit*)target->gameObject;
		if (unit->GetState() == UnitState::RUN)
		{
			unit->PushedOut(this);
		}

	}
}