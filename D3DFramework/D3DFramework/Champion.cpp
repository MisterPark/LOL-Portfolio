﻿#include "stdafx.h"
#include "Champion.h"
#include "FloatingBar.h"
#include "FloatingHPBar.h"
#include "Collider.h"

Champion::Champion()
{
	bar = (FloatingBar*)SceneManager::GetCurrentScene()->CreateObject<FloatingBar>(Layer::UI);
	bar->SetTarget(this);
	hpBar = (FloatingHPBar*)SceneManager::GetCurrentScene()->CreateObject<FloatingHPBar>(Layer::UI);
	hpBar->SetTarget(this);
	stat->SetBaseValue(StatType::MaxExperience, 90.f);
}

Champion::~Champion()
{
	bar = nullptr;
}

void Champion::Initialize()
{
	Unit::Initialize();

}

void Champion::Release()
{
	Unit::Release();
}

void Champion::Update()
{
	Unit::Update();
}

void Champion::OnCollisionEnter(Collider* target)
{
	if (dynamic_cast<Unit*>(target->gameObject))
	{
		Unit* unit = (Unit*)target->gameObject;
		if (unit->GetState() == State::RUN)
		{
			unit->PushedOut(this);
		}
		
	}
}

void Champion::SetTeam(Team _team)
{
	Unit::SetTeam(_team);

	if (_team == Team::BLUE)
	{
		bar->SetTextureHP(L"bar_float (5)");
	}
	else
	{
		bar->SetTextureHP(L"bar_float (2)");
	}
}

void Champion::SetNickname(const std::wstring& _nickname)
{
	nickname = _nickname;
	bar->SetNickname(_nickname);
}

void Champion::OnHit(Unit* target)
{
	for (int i = 0; i < (int)SkillIndex::END; i++) {
		if (skillList[i] != nullptr)
			skillList[i]->OnHit(target);
	}
	for (int i = 0; i < INVENTORY_MAX; i++)
	{
		if (inventory.GetItem(i) != nullptr) {
			for (auto& itemSkill : inventory.GetItem(i)->skillList)
				itemSkill->OnHit(target);
		}
	}
}

void Champion::OnDamaged(Unit* target, float damage)
{
	for (int i = 0; i < (int)SkillIndex::END; i++) {
		if (skillList[i] != nullptr)
			skillList[i]->OnDamaged(damage);
	}
	for (int i = 0; i < INVENTORY_MAX; i++)
	{
		if (inventory.GetItem(i) != nullptr) {
			for (auto& itemSkill : inventory.GetItem(i)->skillList)
				itemSkill->OnDamaged(damage);
		}
	}
}
