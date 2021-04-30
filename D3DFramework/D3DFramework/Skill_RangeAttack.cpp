#include "stdafx.h"
#include "Skill_RangeAttack.h"
#include "Unit.h"
#include "Missile.h"

Skill_RangeAttack::Skill_RangeAttack(Unit* _hostUnit)
{
	maxLevel = 1;
	level = 1;
	host = _hostUnit;
	coolTime = 1.f / host->stat->GetValue(StatType::AttackSpeed);
	coolTimeTick = coolTime;
	range = host->stat->GetValue(StatType::Range);
}

Skill_RangeAttack::~Skill_RangeAttack()
{
}

void Skill_RangeAttack::Start()
{
	coolTime = 1.f / host->stat->GetValue(StatType::AttackSpeed);
	duration = 1.f / host->stat->GetValue(StatType::AttackSpeed);
	range = host->stat->GetValue(StatType::Range);

	if (GetCooltime() > 0.f) return;
	Skill::Start();

	
}

void Skill_RangeAttack::Passive()
{
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}
}

void Skill_RangeAttack::Active()
{
	if (host->attackTarget == nullptr)
	{
		End();
		return;
	}
	else
	{
		if (host->attackTarget->IsDead())
		{
			host->attackTarget = nullptr;
			End();
			return;
		}
	}
	float dt = Time::DeltaTime();

	if (beginAttackFlag == false)
	{
		beginAttackFlag = true;
		host->OnAttackBegin();
	}

	Vector3 direction = host->attackTarget->transform->position - host->transform->position;
	host->agent->Stop();
	host->LookRotation(direction.Normalized());
	host->SetState(host->attackState);

	tick += dt;
	duration = 1.f / host->stat->GetValue(StatType::AttackSpeed);
	if (tick > duration)
	{
		End();
		return;
	}
	float damageDelay = duration * 0.15f;
	if (tick > damageDelay)
	{
		if (host->attackFlag == false)
		{
			host->attackFlag = true;

			Missile* missile = (Missile*)SceneManager::GetCurrentScene()->CreateObject<Missile>(Layer::Effect);
			missile->SetOwner(host, this);
			missile->SetTexture(this->textureKey);
			missile->SetTarget(host->attackTarget);
			missile->transform->position = host->transform->position;

			if (host->attackBeginSound.compare(L""))
				SoundManager::GetInstance()->PlayOverlapSound(host->attackBeginSound.c_str(), SoundChannel::EFFECT, 0.6f);
		}
	}
}

void Skill_RangeAttack::End()
{
	active = true;
	tick = 0.f;
	host->OnAttackEnd();
	host->attackFlag = false;
	beginAttackFlag = false;
}

void Skill_RangeAttack::AttackCancleToAttack()
{
	Start();
	tick = 0.f;
}

void Skill_RangeAttack::SetTexture(const wstring& _key)
{
	this->textureKey = _key;
}
