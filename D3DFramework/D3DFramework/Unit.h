#pragma once
#include "GameObject.h"


enum class UnitState
{
	IDLE1,
	IDLE2,
	IDLE3,
	DEATH,
	RECALL,
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
};

