#include "stdafx.h"
#include "TurretMissile.h"
#include "Plane.h"
#include "Rectangle.h"
#include "SphereCollider.h"
#include "ForwardRenderer.h"
#include "Camera.h"

TurretMissile::TurretMissile()
{
	//base = CreateChild<TurretMissileBase>(L"base");

	mesh = (Engine::Plane*)AddComponent<Engine::Plane>(L"Mesh");
	mesh->SetTexture(L"sru_chaos_cm_ba_mis_tex");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);
	mesh->SetCullMode(CullMode::NONE);
	transform->scale = { 0.75f,0.75f, 0.75f };
	ForwardRenderer* renderer = new ForwardRenderer{ this, L"./forward.fx" };
	renderer->SetMesh(mesh);
	renderer->SetDiffuseTextureParam("g_diffuseTexture");
	AddComponent(L"renderer", renderer);
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
	Billboard();
	transform->Update();

	if (attackTarget != nullptr)
	{
		Vector3 targetPos = attackTarget->transform->position;
		targetPos.y += 1.f;
		Vector3 to =  targetPos - transform->position;
		transform->position += to.Normalized() * movementSpeed * Time::DeltaTime();

		float dist = to.Length();
		if (dist < 0.5f)
		{
			attackTarget->TakeDamage(attackDamage);
			Destroy();
		}
	}

	if (attackTarget != nullptr)
	{
		float angleY = Vector3::AngleY(transform->position, attackTarget->transform->position);
		angle = -angleY + D3DXToRadian(180.f);
		transform->RotateYaw(angle);
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

