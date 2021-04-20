﻿#include "stdafx.h"
#include "TargetingSkill.h"
#include "Unit.h"
#include "PlayerController.h"
#include "SphereCollider.h"

TargetingSkill::TargetingSkill()
{
}

TargetingSkill::~TargetingSkill()
{
}

void TargetingSkill::Use()
{
	if (host == nullptr || level == 0) return;
	PlayerController* controller = host->GetComponent<PlayerController>();
	controller->SetTargetMode(true);
	host->SetNextSkillReady(this);
}

bool TargetingSkill::InRange()
{
	return IsTargetInRange();
}

bool TargetingSkill::IsTargetInRange()
{
	if (host == nullptr) return false;
	if (host->attackTarget == nullptr) return false;
	Vector3 direction = host->attackTarget->transform->position - host->transform->position;
	float dist = direction.Length();
	float targetRadius = host->attackTarget->collider->GetRadius();
	if (dist <= range + targetRadius)
	{
		return true;
	}
	return false;
}

bool TargetingSkill::IsPositionInRange()
{
	if (host == nullptr) return false;
	Vector3 direction = host->attackPoint - host->transform->position;
	float dist = direction.Length();
	if (dist <= range)
	{
		return true;
	}
	return false;
}
