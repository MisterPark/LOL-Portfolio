#pragma once
#include "SkillName.h"

class Character;

class Skill abstract
{
public:
	Skill();
	virtual ~Skill();

public:
	virtual void InitCoolTime() = 0;
	virtual void InitActiveTime() = 0;
	virtual void Update() = 0;
	virtual bool Active(Character* _character);
	virtual void CalcActiveTime();
	virtual void CalcCoolTime();

public:
	// Setter
	void SetIsActive(bool active) { isActive = active; }
	void SetNoneActive();
	
public:
	// Getter
	TextureID GetSkillIcon();
	float GetCoolTime();
	float GetMaxCoolTime();
	float GetActiveTime();
	float GetMoveStopTime();

	bool GetIsCoolDown();
	bool GetIsActive();
	bool GetCanMove();

protected:
	TextureID skillIcon;
	Character* character;
	float coolTime;
	float maxCoolTime;
	float activeTime;
	float moveStopTime;
	bool isCoolDownNow;
	bool isActive;
	bool canMove;
};