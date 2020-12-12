#pragma once
#include "GameObject.h"

class TestGaren : public GameObject
{
public:
	TestGaren();
	virtual ~TestGaren();

	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update() override;

private:
	int currentAnimKey = 0;
};

