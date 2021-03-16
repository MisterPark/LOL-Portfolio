﻿#include "stdafx.h"
#include "Turret.h"
#include "SphereCollider.h"
#include "TurretFloatingBar.h"
#include "TurretMissile.h"
#include "Indicator.h"
#include "TurretBreak.h"
#include "DeferredStaticMeshRenderer.h"
#include "DistortionRenderer.h"
#include "FogOfWarRenderer.h"

Turret::Turret()
{
	transform->position = { 0,0,0 };
	transform->scale = { 0.00015f, 0.00015f, 0.00015f, };
	
	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"turret_order");
	AddComponent(L"StaticMesh", mesh);

	collider->SetRadius(0.6f);

	bar = (TurretFloatingBar*)SceneManager::GetCurrentScene()->CreateObject<TurretFloatingBar>(Layer::UI);
	bar->SetTarget(this);

	stat->SetBaseValue(StatType::Range, 7.75f);

	Engine::DeferredStaticMeshRenderer* renderer =
		(Engine::DeferredStaticMeshRenderer*)AddComponent<Engine::DeferredStaticMeshRenderer>(L"renderer");
	Engine::FogOfWarRenderer* fogOfWarRenderer = new Engine::FogOfWarRenderer(this, 4.f);
	AddComponent(L"fogRenderer", fogOfWarRenderer);
	renderer->SetMesh(mesh);
	renderer->EnableRimLight({ 0.f, 0.f, 1.f });
	Engine::DistortionRenderer* distortionRenderer = new Engine::DistortionRenderer(this);
	AddComponent(L"distortionRenderer", distortionRenderer);
	distortionRenderer->SetMesh(mesh);
	distortionRenderer->SetOpacity(1.0f);

	// 스탯
	stat->SetBaseValue(StatType::MaxHealth, 620.f);
	stat->SetBaseValue(StatType::Health, 620.f);
	stat->SetBaseValue(StatType::HealthRegen, 8.f);
	stat->SetBaseValue(StatType::AttackDamage, 66.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.625f);
	stat->SetBaseValue(StatType::Armor, 36.f);
	stat->SetBaseValue(StatType::MagicResistance, 32.1f);
	stat->SetBaseValue(StatType::Range, 7.75f);
}

Turret::~Turret()
{
	bar = nullptr;

}

void Turret::Update()
{
	// 타겟팅
	if (attackTarget == nullptr)
	{
		attackTarget = GetNearestEnemy(transform->position, (*stat)[StatType::Range]);
	}
	else
	{
		Vector3 to = attackTarget->transform->position - transform->position;
		float dist = to.Length();
		if (dist > (*stat)[StatType::Range])
		{
			attackTarget = nullptr;
		}
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

void Turret::DeadAction()
{
	float dt = Time::DeltaTime();

	if (breakDist < breakHeight)
	{
		breakDist += dt;
		transform->position.y -= dt;
	}
}

void Turret::AttackAction()
{
	float dt = Time::DeltaTime();

	if (attackTarget->IsDead())
	{
		attackTarget = nullptr;
		return;
	}
	attackIndicator->visible = true;

	attackTick += Time::DeltaTime();
	float delay = 1.f / (*stat)[StatType::AttackSpeed];
	if (attackTick >= delay)
	{
		attackTick = 0.f;

		Vector3 missilePos = transform->position;
		missilePos += transform->right.Normalized();
		missilePos.y += 3.f;

		TurretMissile* missile = (TurretMissile*)SceneManager::GetCurrentScene()->CreateObject<TurretMissile>(Layer::Effect);
		missile->transform->position = missilePos;
		missile->SetTeam(team);
		missile->SetAttackTarget(attackTarget);
		//missile->BillboardYaw();
	}


}

void Turret::CounterAttack()
{
}

void Turret::IdleAction()
{
	Unit::IdleAction();
	attackIndicator->visible = false;

}

void Turret::MoveAction()
{
}
