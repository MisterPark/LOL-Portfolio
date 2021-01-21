#include "stdafx.h"
#include "Unit.h"
#include "SphereCollider.h"
#include "NavMeshAgent.h"

Unit::Unit()
{
	SphereCollider* collider = (SphereCollider*)AddComponent<SphereCollider>(L"SphereCollider");
	collider->radius = 1.5f;
	collider->center = { 0.f,1.f,0.f };

	agent = (NavMeshAgent*)AddComponent< NavMeshAgent>(L"NavMeshAgent");
}

Unit::~Unit()
{
	agent = nullptr;
}

void Unit::Initialize()
{
}

void Unit::Release()
{
}

void Unit::Update()
{
	state = UnitState::IDLE1;

	UpdateAttack();

	GameObject::Update();

}

void Unit::UpdateAttack()
{
	float dt = TimeManager::DeltaTime();
	


	if (attackTarget != nullptr)
	{
		Vector3 direction = attackTarget->transform->position - transform->position;
		float dist = direction.Length();
		if (dist <= attackRange) // 공격 거리 이내
		{
			LookRotation(direction.Normalized());
			state = attackState;

			attackTick += dt;
			float attackDelay = 1.f / attackPerSec;
			if (attackTick > attackDelay)
			{
				attackTick = 0.f;
				canAttack = true;
			}
			float damageDelay = attackDelay * 0.1f;
			if (attackTick > damageDelay)
			{
				if (isDamaged == false)
				{
					isDamaged = true;
					attackTarget->hp -= attackDamege;
				}
			}
			

			if (canAttack == false) return;


			canAttack = false;
			isDamaged = false;
		}
	}
	else
	{
		isDamaged = false;
	}
	
}

void Unit::LookRotation(Vector3 _direction)
{
	float angle = Vector3::AngleY(Vector3(0, 0, 1), _direction);
	transform->eulerAngles.y = angle;
	

}

void Unit::SetDestination(Vector3 _target)
{
	
	Vector3 direction = _target - transform->position;
	Vector3::Normalize(&direction);

	// 이동
	Ray ray2;
	RaycastHit hit2;
	ray2.origin = transform->position;
	ray2.origin.y += 0.1f;
	ray2.direction = direction;
	float dist = Vector3(_target - ray2.origin).Length();
	int mask2 = LayerMask::GetMask(Layer::Wall);
	if (Physics::Raycast(ray2, &hit2, dist, mask2))
	{
		// 직선상에 벽이 있을 경우
		Debug::Print("직선상에 벽이있음\n");
		agent->SetDestination(_target);
	}
	else
	{
		// 직선상에 벽이 없을 경우
		agent->SetDestination(_target, true);
	}
}

void Unit::Move(Vector3 _target)
{
	SetAttackTarget(nullptr);
	agent->SetStoppingDistance(0.03f);
	SetDestination(_target);
}

void Unit::Attack(Unit* target)
{
	if (target == nullptr) return;

	attackTarget = target;
	
	agent->SetStoppingDistance(attackRange);
	SetDestination(attackTarget->transform->position);
}

void Unit::Spell1()
{
}

void Unit::Spell2()
{
}

void Unit::Spell3()
{
}

void Unit::Spell4()
{
}

void Unit::SetTeam(Team _team)
{
	team = _team;
}

void Unit::SetAttackTarget(Unit* _target)
{
	attackTarget = _target;
}

void Unit::SetAttackSpeed(float _attackPerSec)
{
	attackPerSec = _attackPerSec;
}
