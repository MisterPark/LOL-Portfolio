#include "stdafx.h"
#include "TurretMissile.h"
#include "Rectangle.h"
#include "SphereCollider.h"

TurretMissile::TurretMissile()
{
	mesh = (Engine::Rectangle*)AddComponent<Engine::Rectangle>(L"Mesh");
	mesh->SetTexture(L"sru_chaos_cm_ba_mis_tex");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);
	mesh->SetCullMode(CullMode::NONE);
	transform->scale = { 0.5f,0.5f, 1.f };
}

TurretMissile::~TurretMissile()
{
	mesh = nullptr;
}

void TurretMissile::Initialize()
{
}

void TurretMissile::Release()
{
}


void TurretMissile::Update()
{
	if (attackTarget != nullptr)
	{
		Vector3 targetPos = attackTarget->transform->position;
		targetPos.y += 1.f;
		Vector3 to =  targetPos - transform->position;
		transform->position += to.Normalized() * movementSpeed * Time::DeltaTime();

		float dist = to.Length();
		if (dist < 0.1f)
		{
			attackTarget->TakeDamage(attackDamage);
			Destroy();
		}
	}

	if (attackTarget != nullptr)
	{
		FaceTarget(attackTarget->transform->position);
	}

	GameObject::Update();
	
	
}

void TurretMissile::SetTeam(Team _team)
{
	team = _team;

	if (_team == Team::BLUE)
	{
		mesh->SetTexture(L"sru_chaos_cm_ba_mis_tex_blue");
	}
	else
	{
		mesh->SetTexture(L"sru_chaos_cm_ba_mis_tex");
	}
}

void TurretMissile::SetAttackTarget(Unit* _target)
{
	attackTarget = _target;
}

