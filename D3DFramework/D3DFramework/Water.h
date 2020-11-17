#pragma once
#include "GameObject.h"
#include "Terrain.h"
#include "Animation2D.h"
class Water : public GameObject
{
public:
	Water();
	virtual ~Water();

	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update() override;

	void WaterTextureChange(TextureKey _StartKey, TextureKey _EndKey, bool _isLoop, float _delay = 1.f);
	void Lava();
	void Beach();
	void Normal();
	Animation2D* anim = nullptr;
	Terrain* terrain = nullptr;
	
private:
	float animSpeed;

	TextureKey startKey;
	TextureKey endKey;

	bool isLoop;
	
};
