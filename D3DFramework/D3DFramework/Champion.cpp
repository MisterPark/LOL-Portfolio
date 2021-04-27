#include "stdafx.h"
#include "Champion.h"
#include "FloatingBar.h"
#include "FloatingHPBar.h"
#include "Collider.h"
#include "Minion.h"
#include "ScorePanel.h"
#include "MiniScorePanel.h"

Champion::Champion()
{
	bar = (FloatingBar*)SceneManager::GetCurrentScene()->CreateObject<FloatingBar>(Layer::UI);
	bar->SetTarget(this);
	hpBar = (FloatingHPBar*)SceneManager::GetCurrentScene()->CreateObject<FloatingHPBar>(Layer::UI);
	hpBar->SetTarget(this);
	stat->SetBaseValue(StatType::MaxExperience, 90.f);
	stat->SetBaseValue(StatType::Level, 1.f);
	stat->SetBaseValue(StatType::SkillPoint, 1.f);
	stat->SetBaseValue(StatType::Bounty, 300.f);
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

	RealTimeGoldIncrease();
	for (int i = 0; i < INVENTORY_MAX; i++)
	{
		Item* item = inventory.GetItem(i);
		if (item == nullptr)
			continue;
		item->Passive();
	}
	for (auto& itemSkill : itemSkillList)
	{
		itemSkill->Passive();
	}
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

void Champion::Die()
{
	Unit::Die();
	stat->IncreaseBaseValue(StatType::DeathScore, 1.f);

	if (unitID == (int)UnitID::Champ0)
		SoundManager::GetInstance()->PlayOverlapSound(L"적에게당했습니다.wav", SoundChannel::EFFECT);
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

	stat->IncreaseBaseValue(StatType::Gold, target->stat->GetBaseValue(StatType::Bounty));

	if (dynamic_cast<Champion*>(target) != nullptr) {
		stat->IncreaseBaseValue(StatType::KillScore, 1.f);
		if(team == Team::BLUE)
			ScorePanel::GetInstance()->AddPublicScore(PublicScoreID::BlueTeamKillScore);
		else if (team == Team::RED)
				ScorePanel::GetInstance()->AddPublicScore(PublicScoreID::RedTeamKillScore);
		MiniScorePanel::GetInstance()->SetBlueTeamKillScore(ScorePanel::GetInstance()->GetPublicScore(PublicScoreID::BlueTeamKillScore));
		MiniScorePanel::GetInstance()->SetRedTeamKillScore(ScorePanel::GetInstance()->GetPublicScore(PublicScoreID::RedTeamKillScore));
		if(unitID == (int)UnitID::Champ0)
			SoundManager::GetInstance()->PlayOverlapSound(L"적을처치했습니다.wav", SoundChannel::EFFECT);
	}
	else if(dynamic_cast<Minion*>(target) != nullptr)
		stat->IncreaseBaseValue(StatType::MinionKilled, 1.f);

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

void Champion::RealTimeGoldIncrease()
{
	realTimeGoldTick += Time::DeltaTime();
	if (realTimeGoldTick > 1.f)
	{
		realTimeGoldTick--;
		stat->IncreaseBaseValue(StatType::Gold, 1.6f);
	}
}