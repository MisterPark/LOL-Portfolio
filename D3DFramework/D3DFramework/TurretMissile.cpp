#include "stdafx.h"
#include "TurretMissile.h"
#include "Plane.h"
#include "Rectangle.h"
#include "SphereCollider.h"
#include "ForwardRenderer.h"
#include "Camera.h"

TurretMissile::TurretMissile()
{
	//mesh = (Engine::Plane*)AddComponent<Engine::Plane>(L"Mesh");
	//mesh->SetTexture(L"sru_chaos_cm_ba_mis_tex");
	//mesh->SetBlendMode(BlendMode::ALPHA_BLEND);
	//mesh->SetCullMode(CullMode::NONE);
	//transform->scale = { 0.75f,0.75f, 0.75f };
	//ForwardRenderer* renderer = new ForwardRenderer{ this, L"./forward.fx" };
	//renderer->SetMesh(mesh);
	//renderer->SetDiffuseTextureParam("g_diffuseTexture");
	//AddComponent(L"renderer", renderer);

	base = CreateChild<TurretMissileBase>(L"base");
}

TurretMissile::~TurretMissile()
{
	mesh = nullptr;
	base = nullptr;
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
		//FaceTarget(attackTarget->transform->position);
		//Billboard();
		
		float angle = Vector3::AngleY(transform->position, attackTarget->transform->position);
		Vector3 axis = Camera::main->transform->position - Camera::main->transform->look;
		axis.x = -axis.x;
		axis.z = -axis.z;

		Vector3::Normalize(&axis);
		transform->Rotate(axis, angle);

	}

	GameObject::Update();
	
	
}

void TurretMissile::SetTeam(Team _team)
{
	team = _team;

	if (_team == Team::BLUE)
	{
		base->mesh->SetTexture(L"sru_chaos_cm_ba_mis_tex_blue");
	}
	else
	{
		base->mesh->SetTexture(L"sru_chaos_cm_ba_mis_tex");
	}
}

void TurretMissile::SetAttackTarget(Unit* _target)
{
	attackTarget = _target;
}

