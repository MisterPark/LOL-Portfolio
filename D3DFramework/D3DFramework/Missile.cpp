#include "stdafx.h"
#include "Missile.h"
#include "Plane.h"

Missile::Missile()
{
	mesh = (Engine::Plane*)AddComponent<Engine::Plane>(L"Mesh");
	mesh->SetTexture(L"missfortune_base_e_musketball");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);
	mesh->SetCullMode(CullMode::NONE);
	transform->scale = { 0.1f,0.1f, 0.1f };
	ForwardRenderer* renderer = new ForwardRenderer{ this, L"./forward.fx" };
	renderer->SetMesh(mesh);
	renderer->SetDiffuseTextureParam("g_diffuseTexture");
	AddComponent(L"renderer", renderer);
}

Missile::~Missile()
{
	owner = nullptr;
	mesh = nullptr;
}

void Missile::Initialize()
{
}

void Missile::Release()
{
}

void Missile::Update()
{
	Billboard();
	transform->Update();

	if (attackTarget != nullptr)
	{
		Vector3 targetPos = attackTarget->transform->position;
		targetPos.y += 1.f;
		Vector3 to = targetPos - transform->position;
		transform->position += to.Normalized() * movementSpeed * Time::DeltaTime();

		float dist = to.Length();
		if (dist < 0.5f)
		{

			attackTarget->SetLastAttacker(owner);
			float finalDamage = owner->stat->GetValue(StatType::AttackDamage);
			owner->Calc_FinalDamage(&finalDamage, owner->stat, attackTarget->stat);
			owner->OnHit(attackTarget);
			attackTarget->TakeDamage(finalDamage);
			// 피격정보 저장
			Unit::HitInfo info;
			info.damageSum += finalDamage;
			info.unit = owner;

			auto iter = attackTarget->hitList.begin();
			auto end = attackTarget->hitList.end();
			for (; iter != end;)
			{
				if ((*iter).unit == owner)
				{
					info.damageSum += (*iter).damageSum;
					iter = attackTarget->hitList.erase(iter);
					break;
				}
				++iter;
			}

			attackTarget->hitList.push_back(info);
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

void Missile::SetOwner(Unit* _owner)
{
	this->owner = _owner;
}

void Missile::SetTexture(const wstring& _key)
{
	if (mesh == nullptr) return;
	mesh->SetTexture(_key);
}

void Missile::SetTarget(Unit* _target)
{
	this->attackTarget = _target;
}
