#include "stdafx.h"
#include "Minion.h"
#include "MinionFloatingBar.h"
#include "MinionAI.h"
#include "SphereCollider.h"
#include "MinionSubTree.h"
#include "Skill_Attack.h"

Minion::Minion()
{
	SetSpawnTime(INFINITY);

	bar = (MinionFloatingBar*)SceneManager::GetCurrentScene()->CreateObject<MinionFloatingBar>(Layer::UI);
	bar->SetTarget(this);

	ai =(MinionAI*)AddComponent<MinionAI>(L"AI");

	// 스킬
	skillList[(int)SkillIndex::Attack] = new Skill_Attack(this);

	MinionSubTree* subTree = new MinionSubTree(this);
	bt->SetRoot(subTree);
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
		if (unit->GetState() == State::RUN)
		{
			unit->PushedOut(this);
		}

	}
}