#pragma once

#include "UI.h"
#include "Vertex.h"

class UIManager
{
	UIManager();
	virtual ~UIManager();

public:
	static UIManager* GetInstance();
	static void DestroyInstance();

	void AddUI(UI* _ui);
	void DeleteListAll(); // 리스트에서 삭제만 해주는것

	list<UI*> ui;
};