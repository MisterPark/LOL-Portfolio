#pragma once
#include "GameObject.h"

class Enemy02 :
	public GameObject
{
public:
	explicit Enemy02();
	explicit Enemy02(Vector3 pos, Vector3 look, int type = 1, GameObject* target = nullptr);
	virtual ~Enemy02();

	// GameObject을(를) 통해 상속됨
	void Ready();
	virtual void Update() override;
	void Pattern01();
	void Pattern02();
	void Pattern03();
	void Pattern01Bullet();
	void Pattern02Bullet();
	void Pattern03Bullet();
	virtual void OnCollision(GameObject* from);

	bool Culling();

private:
	bool canAttack = true;
	float coolTime = 0.f;
	int type = 1;
	int spawnPattern = 1;
	bool isChange = false;
	GameObject* target;
};

