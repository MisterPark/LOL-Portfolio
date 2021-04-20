#include "stdafx.h"
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

void Champion::OnHit(Unit* target, Skill* mySkill)
{
	for (int i = 0; i < (int)SkillIndex::END; i++) {
		if (skillList[i] != nullptr)
			skillList[i]->OnHit(target, mySkill);
	}
	for (auto& itemSkill : itemSkillList)
		itemSkill->OnHit(target, mySkill);
	mySkill->OnThisSkillHit(target);
}

void Champion::OnDamaged(Unit* target, Skill* targetSkill, float* damage)
{
	for (int i = 0; i < (int)SkillIndex::END; i++) {
		if (skillList[i] != nullptr)
			skillList[i]->OnDamaged(target, targetSkill, damage);
	}

	for (auto& itemSkill : itemSkillList)
		itemSkill->OnDamaged(target, targetSkill, damage);
}

void Champion::OnKilled(Unit* target)
{
	Unit::OnKilled(target);
	for (int i = 0; i < (int)SkillIndex::END; i++) {
		if (skillList[i] != nullptr)
			skillList[i]->OnKilled(target);
	}

	for (auto& itemSkill : itemSkillList)
		itemSkill->OnKilled(target);

}

void Champion::OnOtherSkillStart(Skill* otherSkill)
{
	for (auto& itemSkill : itemSkillList)
		itemSkill->OnOtherSkillStart(otherSkill);
}

void Champion::OnTargetFirstHit(Unit* target, Skill* mySkill)
{
	for (auto& itemSkill : itemSkillList)
		itemSkill->OnTargetFirstHit(target, mySkill);
}
