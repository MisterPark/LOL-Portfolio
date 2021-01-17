#pragma once
#include "GameObject.h"

using namespace std;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void Update();

private:
	list<GameObject*> objectTable[MaxOfEnum<Layer>()];
};

