#pragma once
class Component
{
public:
	Component();
	virtual ~Component();
	virtual void Initialize() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;

	wstring componentName;
	GameObject* gameObject = nullptr;
};

