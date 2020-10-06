#pragma once
#include "Component.h"
class MoveComponent :
	public Component
{
public:
	MoveComponent();
	virtual ~MoveComponent();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update() override;
	

};

