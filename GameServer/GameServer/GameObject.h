#pragma once
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update() = 0;
};

