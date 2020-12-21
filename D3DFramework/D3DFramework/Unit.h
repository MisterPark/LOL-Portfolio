#pragma once
#include "GameObject.h"
#include "Animation.h"

enum class Team
{
	NEUTRAL, BLUE, RED, END
};

enum class UnitState
{
	IDLE1,
	IDLE2,
	IDLE3,
	DEATH,
	RECALL,
	RECALL2,
	RECALL3,
	RUN,
	RUN_HASTE,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	ATTACK4,
	CRITICAL,
	Q,
	W,
	E,
	R,
	Q2,
	W2,
	E2,
	R2,
	END
};

class Unit : public GameObject
{
public:
    Unit();
    virtual ~Unit();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

public:
	UnitState state = UnitState::IDLE1;
	Team team = Team::NEUTRAL;
	Animation* anim = nullptr;
};

