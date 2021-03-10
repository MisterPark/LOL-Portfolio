#pragma once
#include "GameObject.h"

using namespace Engine;


enum class ItemType
{
	None,
	Boots,
	End
};

class Item :
	public GameObject
{
public:
	// GameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update() override;

	virtual void Use() = 0;

	ItemType type = ItemType::None;
	UINT count = 1;
	Animation2D* anim;
};

