#pragma once
#include "GameObject.h"

using namespace PKH;

class Environment :
	public GameObject
{
public:
	Environment();
	virtual ~Environment();
	// GameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update() override;
};

