#pragma once
#include "GameObject.h"
#include "Rectangle.h"

using namespace Engine;

class FloatingHPBar : public GameObject
{
public:
	FloatingHPBar();
	virtual ~FloatingHPBar();

	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update() override;

	void SetTarget(GameObject* target);

protected:
	GameObject* target = nullptr;

	Vector3 offset;
	Engine::Rectangle* mesh = nullptr;
};

