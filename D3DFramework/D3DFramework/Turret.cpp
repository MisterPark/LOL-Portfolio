#include "stdafx.h"
#include "Turret.h"
#include "SphereCollider.h"
#include "TurretFloatingBar.h"
#include "TurretMissile.h"
#include "Indicator.h"
#include "TurretBreak.h"

Turret::Turret()
{
	transform->position = { 0,0,0 };
	transform->scale = { 0.00015f, 0.00015f, 0.00015f, };
	
	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"turret_order");
	AddComponent(L"StaticMesh", mesh);

	collider->SetRadius(0.6f);

	bar = (TurretFloatingBar*)ObjectManager::GetInstance()->CreateObject<TurretFloatingBar>(Layer::UI);
	bar->SetTarget(this);

	SetAttackRange(7.75f);
}

Turret::~Turret()
{
	bar = nullptr;
}

void Turret::Update()
{
	float dt = TimeManager::DeltaTime();

	if (isDead)
	{

		if (breakDist < breakHeight)
		{
			breakDist += dt;
			transform->position.y -= dt;
		}
		GameObject::Update();
		return;
	}
	// Å¸°ÙÆÃ
	if (attackTarget == nullptr)
	{
		attackTarget = GetNearestEnemy(transform->position, attackRange);
	}
	else
	{
		Vector3 to = attackTarget->transform->position - transform->position;
		float dist = to.Length();
		if (dist > attackRange)
		{
			attackTarget = nullptr;
		}
	}

	if (attackTarget != nullptr)
	{
		if (attackTarget->IsDead())
		{
			attackTarget = nullptr;
			return;
		}
		attackIndicator->isVisible = true;

		attackTick += TimeManager::DeltaTime();
		float delay = 1.f / attackPerSec;
		if (attackTick >= delay)
		{
			attackTick = 0.f;

			Vector3 missilePos = transform->position;
			missilePos += transform->right.Normalized();
			missilePos.y += 3.f;

			TurretMissile* missile = (TurretMissile*)ObjectManager::GetInstance()->CreateObject<TurretMissile>(Layer::Effect);
			missile->transform->position = missilePos;
			missile->SetTeam(team);
			missile->SetAttackTarget(attackTarget);
			missile->Billboard();
		}
		
	}
	else
	{
		attackIndicator->isVisible = false;
	}

	GameObject::Update();
}


void Turret::SetTeam(Team _team)
{
	Unit::SetTeam(_team);
	
	if (_team == Team::BLUE)
	{
		bar->SetTextureHP(L"bar_float (5)");
	}
	else
	{
		bar->SetTextureHP(L"bar_float (2)");
	}
}
