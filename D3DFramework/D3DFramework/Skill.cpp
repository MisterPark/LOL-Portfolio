#include "stdafx.h"
#include "Skill.h"
#include "Unit.h"
#include "DamageCalc.h"
#include "TestScene.h"
#include "SphereCollider.h"

Skill::Skill()
{
}

Skill::~Skill()
{
	for (auto calc : damageCalcList)
	{
		delete calc;
	}
}

void Skill::Use()
{
	if (level == 0)
		return;
	Start();
}

void Skill::Start()
{
	active = true;
	coolTimeTick = 0.f;
	firstHit = false;
	hitList.clear();
}

void Skill::Passive()
{
}

void Skill::Active()
{
}

void Skill::End()
{
	active = false;
	tick = 0.f;
}

bool Skill::InRange()
{
	return true;
}

Skill* Skill::Clone()
{
	return nullptr;
}

void Skill::OnHit(Unit* target, Skill* mySkill)
{
}

void Skill::OnDamaged(Unit* target, Skill* targetSkill, float* damage)
{
}

void Skill::OnKilled(Unit* target)
{
}

void Skill::OnThisSkillHit(Unit* target)
{
	if (!firstHit) {
		OnOtherSkillStart(this);
		firstHit = true;
	}
}

void Skill::OnOtherSkillStart(Skill* otherSkill)
{
}

void Skill::OnTargetFirstHit(Unit* target, Skill* mySkill)
{
}

bool Skill::PlayerToDistanceCompare(Vector3 _pos, float _distance)
{
	TestScene* scene = dynamic_cast<TestScene*>(SceneManager::GetCurrentScene());
	if (scene != nullptr)
	{
		Unit* player = scene->unitMap.find((int)UnitID::Champ0)->second;
		Vector3 direction = _pos - player->transform->position;
		float dist = direction.Length();
		float targetRadius = player->collider->GetRadius();
		if (dist <= _distance + targetRadius)
		{
			return true;
		}
	}
	return false;
}

bool Skill::IsActive()
{
	return active;
}

bool Skill::IsAvailable()
{
	if (!active)
		return true;
	return false;
}

void Skill::Add_DamageCalc(DamageCalc* _damageCalc)
{
	damageCalcList.emplace_back(_damageCalc);
}

void Skill::Calc_FinalDamage(float* _damage, Stat* _myStat, Stat* _targetStat)
{
	for (auto& calc : damageCalcList)
	{
		calc->Calc(_damage, _myStat, _targetStat);
	}
}

void Skill::Calc_TakeDamege(float _baseDamage)
{
	Unit* target = host->attackTarget;
	target->SetLastAttacker(host);
	float finalDamage = _baseDamage;
	Calc_FinalDamage(&finalDamage, host->stat, target->stat);
	host->attackTarget->OnDamaged(host, this, &finalDamage);
	target->TakeDamage(finalDamage);
	
	// 피격정보 저장
	Unit::HitInfo info;
	info.damageSum += finalDamage;
	info.unit = host;

	auto iter = target->hitList.begin();
	auto end = target->hitList.end();
	for (; iter != end;)
	{
		if ((*iter).unit == host)
		{
			info.damageSum += (*iter).damageSum;
			iter = target->hitList.erase(iter);
			break;
		}
		++iter;
	}

	target->hitList.push_back(info);
	//
	//for (auto& unit : hitList)
	//{
	//	if (unit == target)
	//		return;
	//}
	//hitList.push_back(target);
	host->OnTargetFirstHit(target, this);


}

float Skill::GetCooltime()
{
	return (coolTime - coolTimeTick);
}

float Skill::GetCooltime_Init()
{
	return coolTime;
}

bool Skill::TargetingSuccess(Unit* target)
{
	if (host == nullptr) return false;

	if (target->team != host->team)
		return true;
	return false;
}

void Skill::SetTarget(Unit* _target)
{
	host = _target;
}

