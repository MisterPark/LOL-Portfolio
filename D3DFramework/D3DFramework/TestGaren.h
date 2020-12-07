#pragma once
#include "GameObject.h"

class TestGaren : public GameObject
{
public:
	TestGaren();
	virtual ~TestGaren();



	// GameObject을(를) 통해 상속됨
	virtual void Initialize() override;

	virtual void Release() override;

	virtual void Update() override;

private:
	int currentAnimKey = 0;

};

