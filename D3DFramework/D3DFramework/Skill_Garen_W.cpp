#include "stdafx.h"
#include "Skill_Garen_W.h"
#include "Unit.h"
#include "Buff.h"
#include "Buff_GarenWReduction.h"
#include "Buff_GarenWShield.h"
#include "Buff_GarenWPassive.h"
#include "Effect_Garen_W.h"
#include "Effect_Garen_W_Shield.h"

Skill_Garen_W::Skill_Garen_W(Unit* _hostUnit)
{
	maxLevel = 5;
	coolTime = 7.f;
	coolTimeTick = coolTime;
	duration = 0.f;
	host = _hostUnit;
}

Skill_Garen_W::~Skill_Garen_W()
{
}

void Skill_Garen_W::Start()
{
	if (level == 0 || GetCooltime() > 0.f)
		return;

	Skill::Start();
	host->OnOtherSkillStart(this);


	Effect_Garen_W* eff = (Effect_Garen_W*)SceneManager::GetCurrentScene()->CreateObject<Effect_Garen_W>(Layer::Effect);
	eff->SetTarget(host);
	eff->SetOffset(Vector3(0.f, 0.1f, 0.f));
	eff->SetDuration(2);

	Effect_Garen_W_Shield* effS = (Effect_Garen_W_Shield*)SceneManager::GetCurrentScene()->CreateObject<Effect_Garen_W_Shield>(Layer::Effect);
	effS->SetTarget(host);
	effS->SetOffset(Vector3(0.f, 1.0f, 0.f));
	effS->SetDuration(0.5f);
	effS->transform->eulerAngles.y -= D3DXToRadian(20.f);

	reductionTime = 1.25f + level * 0.75f;
	Buff_GarenWReduction* reductionBuff = new Buff_GarenWReduction(host, reductionTime, 0.5f);//reductionValue);
	host->stat->AddBuff(reductionBuff);

	//TODO : 가렌W 지금은 최대체력계수로 되어있지만 나중에 추가체력계수로 바꿔야함
	float shield = 70 + host->stat->GetValue(StatType::MaxHealth) * 0.2f;
	Buff_GarenWShield* attackBuff = new Buff_GarenWShield(host, 0.75f, shield);
	host->stat->AddBuff(attackBuff);

	if (Random::Value(2) == 0)
		SoundManager::GetInstance()->PlayOverlapSound(L"Voice_GarenW1.ogg", SoundChannel::PLAYER);
	else
		SoundManager::GetInstance()->PlayOverlapSound(L"Voice_GarenW2.ogg", SoundChannel::PLAYER);
	SoundManager::GetInstance()->PlayOverlapSound(L"GarenW1.ogg", SoundChannel::PLAYER_EFFECT);
}

void Skill_Garen_W::Passive()
{

	if (level == 0)
		return;
	
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}
	

	if (passiveBuff == nullptr) {
		passiveBuff = new Buff_GarenWPassive(host);
		host->stat->AddBuff(passiveBuff);
	}

}

void Skill_Garen_W::Active()
{
	End();
}


void Skill_Garen_W::End()
{
	Skill::End();
}

void Skill_Garen_W::OnKilled(Unit* target)
{
	passiveStack++;
	if (passiveBuff != nullptr) {
		passiveBuff->modifiers.front().value = passiveStack * 0.25f;
		passiveBuff->modifiers.back().value = passiveStack * 0.25f;
	}
}
