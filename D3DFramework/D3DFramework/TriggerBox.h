#pragma once
#include "GameObject.h"
#include "Animation2D.h"
class TriggerBox :
	public GameObject
{
public:
	TriggerBox();
	~TriggerBox();

	// GameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update() override;

	virtual void OnCollision(GameObject* target);
	void OnTerrain();

	void Portal();
	void AnimChange(TextureKey _startKey , TextureKey _endKey, float _delay = 0.f , bool _isLoop = false);
	Animation2D* anim = nullptr;
	
public:
	void(*OnTriggered)() = nullptr;
	float offsetY;
private:

};

