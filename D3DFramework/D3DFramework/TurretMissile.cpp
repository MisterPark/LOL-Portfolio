#include "stdafx.h"
#include "TurretMissile.h"
#include "Rectangle.h"
#include "SphereCollider.h"
#include "ForwardRenderer.h"
TurretMissile::TurretMissile()
{
	mesh = (Engine::Rectangle*)AddComponent<Engine::Rectangle>(L"Mesh");
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
		Billboard();

		//Vector3 dir = attackTarget->transform->position - transform->position;
		//dir.y = 0.f;
		//Quaternion qRot;
		//Vector3 axis = Vector3::Cross(dir, Vector3::UP);
		//float angle = acosf(Vector3::Dot(Vector3::UP, dir.Normalized()));
		//D3DXQuaternionRotationAxis(&qRot, &axis, angle);
		//Vector3 euler = Quaternion::ToEulerAngles(qRot);

		//transform->eulerAngles = euler;
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

