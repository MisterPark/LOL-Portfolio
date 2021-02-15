#pragma once
#include "GameObject.h"
#include "HUD.h"

class Champion;
class Label;

class PlayerInfoPanel : public GameObject
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

	virtual void Update() override;

	//void RenderStat();
	//void RenderMini();
	//void RenderBar();

	void SetTarget(Champion* _target);

public:

	int screenW = 1280;
	int screenH = 720;
private:
	Vector3 faceBorderPos;
	Vector3 mainPanelPos;
	Vector3 miniPanelPos;
	Vector3 invenPanelPos;
	Vector3 statPanelPos;
	Vector3 hpOffsetPos;
	Vector3 mpOffsetPos;
	Vector3 scaleHP;
	Vector3 scaleMP;
	Vector3 barTipOffset1;
	Vector3 barTipOffset2;
	Vector3 barTipOffset3;
	Vector3 barTipOffset4;

	Texture* mainPanelTex = nullptr;
	Texture* miniPanelTex = nullptr;
	Texture* faceBorderTex = nullptr;
	Texture* invenPanelTex = nullptr;
	Texture* statPanelTex = nullptr;
	wstring textureKeyHP;
	wstring textureKeyMP;
	wstring tipTextureKey;
	wstring spellBorderKey;

	UI* statPanel = nullptr;
	UI* mainPanel = nullptr;
	UI* miniPanel = nullptr;
	UI* invenPanel = nullptr;
	UI* faceBorder = nullptr;
	UI* facePanel = nullptr;
	Label* hpLabel = nullptr;
	Label* mpLabel = nullptr;

	Label* statLabel[8];

	UI* slotSpell1 = nullptr;
	UI* slotSpell2 = nullptr;
	UI* slotSpell3 = nullptr;
	UI* slotSpell4 = nullptr;
	UI* slotPassive = nullptr;
	UI* slotSummoner1 = nullptr;
	UI* slotSummoner2 = nullptr;

	Champion* champion = nullptr;
};

