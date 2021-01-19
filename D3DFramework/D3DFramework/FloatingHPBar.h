#pragma once
#include "GameObject.h"
#include "Rectangle.h"

using namespace PKH;

class FloatingHPBar : public GameObject
{
public:
	FloatingHPBar();
	virtual ~FloatingHPBar();

	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetTarget(GameObject* target);

protected:
	GameObject* target = nullptr;

	Vector3 offset;
	PKH::Rectangle* mesh = nullptr;
};

