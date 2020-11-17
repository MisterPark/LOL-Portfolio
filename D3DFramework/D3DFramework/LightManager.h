#pragma once

#include "Light.h"

class LightManager
{
private:
	LightManager();
	virtual ~LightManager();


public:
	static LightManager* GetInstance();
	static void Destroy();

	static void RegisterObject(Light* pLight);
	static void DisregisterObject(Light* pLight);

private:
	list<Light*> lightList;
};

