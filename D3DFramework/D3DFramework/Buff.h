#pragma once

class Unit;

class Buff
{
	Buff(float _value, float _duration);

	bool Update();

public:
	Unit* host = nullptr;
	float baseValue = 0.f;
	float tick = 0.f;
	float duration = 0.f;
};

