#include "stdafx.h"
#include "Component.h"


Component::Component()
{
	Initialize();
}

Component::~Component()
{
	Release();
}
