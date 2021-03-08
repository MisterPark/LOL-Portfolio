#pragma once
#include "Panel.h"
class Button;
class ItemshopPanel : public Panel
{
public:
	ItemshopPanel();
	virtual ~ItemshopPanel();

public:
	static ItemshopPanel* GetInstance();
	static void DestroyInstance();

	virtual void Update();

	static void ToggleVisible();
	static void Close();
};