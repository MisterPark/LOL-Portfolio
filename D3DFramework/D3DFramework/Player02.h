#pragma once
#include "GameObject.h"

using namespace PKH;

class Player02 :
	public GameObject
{
public:
	Player02();
	virtual ~Player02();

	// GameObject을(를) 통해 상속됨
	virtual void Update() override;
	void Attack();
	virtual void OnCollision(GameObject* from);
	virtual void PostRender()override;

private:
	bool canAttack = true;
	bool isInvincible = false;
	float coolTime = 0.f;
	int hp = 10;
};

