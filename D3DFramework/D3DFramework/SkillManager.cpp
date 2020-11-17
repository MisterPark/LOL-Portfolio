#include "stdafx.h"
#include "SkillManager.h"
#include "AllSkills.h"

SkillManager* SkillManager::instance = nullptr;

SkillManager::SkillManager()
{
}

SkillManager::~SkillManager()
{
}

SkillManager * SkillManager::GetInstance()
{
	if (nullptr == instance) instance = new SkillManager;
	return instance;
}

void SkillManager::Destroy()
{
	if (nullptr != instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void SkillManager::Update()
{
	for (auto& skill : skillList)
	{
		// 쿨다운이 진행중일 때
		if (skill->GetIsCoolDown())
		{
			skill->CalcCoolTime();
		}

		// 스킬이 액티브 중일 때
		if (skill->GetIsActive())
		{
			skill->Update();
		}
	}
}

void SkillManager::PostUpdate()
{
	for (auto& skill : skillList)
	{
		if (skill->GetIsActive())
		{
			if (0.f > skill->GetActiveTime())
				skill->SetNoneActive();
		}
	}
}

void SkillManager::AddSkillToList(Skill * skill)
{
	if (IsSkillInList(skill)) return;

	skillList.emplace_back(skill);
}

void SkillManager::DeleteSkillFromList(Skill * skill)
{
	auto iter = find_if(skillList.begin(), skillList.end(), [skill](Skill* elem)
	{
		return elem == skill;
	});

	if (skillList.end() == iter) return;

	skillList.erase(iter);
}

bool SkillManager::IsSkillInList(Skill * skill)
{
	auto iter = find_if(skillList.begin(), skillList.end(), [skill](Skill* elem)
	{
		return elem == skill;
	});

	if (skillList.end() == iter) return false;
	return true;
}

Skill * SkillManager::GetSkill(SkillName skillName)
{
	Skill* newSkill = nullptr;

	switch (skillName)
	{
	case SkillName::LeafShot:
		newSkill = Skill_LeafShot::Create();
		break;

	case SkillName::FireBall:
		newSkill = Skill_FireBall::Create();
		break;

	case SkillName::WaterCannon:
		newSkill = Skill_WaterCannon::Create();
		break;

	case SkillName::Blaze:
		newSkill = Skill_Blaze::Create();
		break;
	case SkillName::Tornado:
		newSkill = Skill_Tornado::Create();
		break;
	case SkillName::Rush:
		newSkill = Skill_Rush::Create();
		break;
	case SkillName::TearsShot:
		newSkill = Skill_TearsShot::Create();
		break;
	case SkillName::CrossShot:
		newSkill = Skill_CrossShot::Create();
		break;
	case SkillName::XShot:
		newSkill = Skill_XShot::Create();
		break;
	case SkillName::WebShot:
		newSkill = Skill_WebShot::Create();
		break;
	case SkillName::SnowRain:
		newSkill = Skill_SnowRain::Create();
		break;
	case SkillName::SnowVulcan:
		newSkill = Skill_SnowVulcan::Create();
		break;
	case SkillName::SnowFall:
		newSkill = Skill_SnowFall::Create();
		break;
	case SkillName::SnowCrystal:
		newSkill = Skill_SnowCrystal::Create();
		break;
	case SkillName::BubbleShot:
		newSkill = Skill_BubbleShot::Create();
		break;
	case SkillName::AccelWater:
		newSkill = Skill_AccelWater::Create();
		break;
	case SkillName::XClaw:
		newSkill = Skill_XClaw::Create();
		break;
	case SkillName::HealBubble:
		newSkill = Skill_HealBubble::Create();
		break;
	case SkillName::Meteor:
		newSkill = Skill_Meteor::Create();
		break;
	case SkillName::Quake:
		newSkill = Skill_Quake::Create();
		break;
	case SkillName::FireWallWave:
		newSkill = Skill_FireWallWave::Create();
		break;
	case SkillName::FireBlast:
		newSkill = Skill_FireBlast::Create();
		break;
	case SkillName::ReverseHealBubble:
		newSkill = Skill_ReverseHealBubble::Create();
		break;
	case SkillName::MiniRush:
		newSkill = Skill_MiniRush::Create();
		break;
	case SkillName::WaterFlow:
		newSkill = Skill_WaterFlow::Create();
		break;
	case SkillName::WaterBomb:
		newSkill = Skill_WaterBomb::Create();
		break;
	case SkillName::Tsunami:
		newSkill = Skill_Tsunami::Create();
		break;
	case SkillName::ShellAttack:
		newSkill = Skill_ShellAttack::Create();
		break;
	case SkillName::LeechSeed:
		newSkill = Skill_LeechSeed::Create();
		break;
	case SkillName::PetalBlizzard:
		newSkill = Skill_PetalBlizzard::Create();
		break;
	case SkillName::ClawBlast:
		newSkill = Skill_ClawBlast::Create();
		break;
	case SkillName::FireShot:
		newSkill = Skill_FireShot::Create();
		break;
	case SkillName::FireBomb:
		newSkill = Skill_FireBomb::Create();
		break;
	case SkillName::FireXCrossBomb:
		newSkill = Skill_FireXCrossBomb::Create();
		break;
	case SkillName::Synthesis:
		newSkill = Skill_Synthesis::Create();
		break;
	case SkillName::RedBall:
		newSkill = Skill_RedBall::Create();
		break;
	case SkillName::Explosion:
		newSkill = Skill_Explosion::Create();
		break;
	case SkillName::DarkBallFall:
		newSkill = Skill_DarkBallFall::Create();
		break;
	case SkillName::GuidEnergyBall:
		newSkill = Skill_GuidEnergyBall::Create();
		break;
	case SkillName::GravityEnergyBall:
		newSkill = Skill_GravityEnergyBall::Create();
		break;
	case SkillName::DiagonalEnergyBall:
		newSkill = Skill_DiagonalEnergyBall::Create();
		break;
	}
	return newSkill;
}
