#include "stdafx.h"
#include "Unit.h"
#include "SphereCollider.h"
#include "NavMeshAgent.h"
#include "Animation.h"

EnemyUnit::EnemyUnit()
{
	anim = (Animation*)AddComponent<Animation>(L"Animation");
	SphereCollider* collider = (SphereCollider*)AddComponent<SphereCollider>(L"SphereCollider");
	collider->radius = 1.5f;
	collider->center = { 0.f,1.f,0.f };

	agent = (NavMeshAgent*)AddComponent< NavMeshAgent>(L"NavMeshAgent");
}

EnemyUnit::~EnemyUnit()
{
	anim = nullptr;
	agent = nullptr;
}

void EnemyUnit::Initialize()
{
}

void EnemyUnit::Release()
{
}

void EnemyUnit::Update()
{
	state = UnitState::IDLE1;

	UpdateAttack();

	GameObject::Update();
}

void EnemyUnit::UpdateAttack()
{
	float dt = TimeManager::DeltaTime();
	attackTick += dt;


	float attackDelay = 1.f / attackPerSec;

	if (attackTick > attackDelay)
	{
		attackTick = 0.f;
		canAttack = true;
		int rand = Random::Range(0, 9);
		if (rand < 5)
		{
			attackState = UnitState::ATTACK1;
		}
		else
		{
			attackState = UnitState::ATTACK2;
		}
	}

	if (attackTarget != nullptr)
	{
		Vector3 direction = attackTarget->transform->position - transform->position;
		float dist = direction.Length();
		if (dist <= attackRange) // 공격 거리 이내
		{
			if (canAttack == false) return;

			LookRotation(direction.Normalized());
			
			state = attackState;
			
			
		}
	}
}

void EnemyUnit::LookRotation(Vector3 _direction)
{
	float angle = Vector3::AngleY(Vector3(0, 0, 1), _direction);
	transform->eulerAngles.y = angle;
	

}

void EnemyUnit::SetDestination(Vector3 _target)
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

void EnemyUnit::Attack(EnemyUnit* target)
{
	if (target == nullptr) return;

	attackTarget = target;
	
	agent->SetStoppingDistance(attackRange);
	SetDestination(attackTarget->transform->position);
}

void EnemyUnit::Spell1()
{
}

void EnemyUnit::Spell2()
{
}

void EnemyUnit::Spell3()
{
}

void EnemyUnit::Spell4()
{
}
