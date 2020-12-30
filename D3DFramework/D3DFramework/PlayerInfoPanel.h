#pragma once
#include "Panel.h"
class PlayerInfoPanel : public UI
{
private:
	PlayerInfoPanel();
	virtual ~PlayerInfoPanel();

public:
	static PlayerInfoPanel* GetInstance();
	static void DestroyInstance();

	// UI을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void UpdateUI() override;

	virtual void Render() override;


public:
	int screenW = 1280;
	int screenH = 720;

	Vector3 faceBorderPos;
	Vector3 mainPanelPos;
	Vector3 miniPanelPos;
	Vector3 invenPanelPos;

	Texture* mainPanelTex = nullptr;
	Texture* miniPanelTex = nullptr;
	Texture* faceBorderTex = nullptr;
	Texture* invenPanelTex = nullptr;
};

