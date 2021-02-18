#pragma once
#include "Panel.h"

class ItemshopPanel : public Panel
{
public:
	ItemshopPanel();
	virtual ~ItemshopPanel();

public:
	static ItemshopPanel* GetInstance();
	static void DestroyInstance();

};