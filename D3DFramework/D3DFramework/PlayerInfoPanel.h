#pragma once
#include "GameObject.h"


class Champion;
class Label;
class PKH::UI;

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
	Texture* mainPanelTex = nullptr;
	Texture* miniPanelTex = nullptr;
	Texture* faceBorderTex = nullptr;
	Texture* invenPanelTex = nullptr;
	Texture* statPanelTex = nullptr;
	wstring textureKeyHP;
	wstring textureKeyMP;
	wstring tipTextureKey;
	wstring spellBorderKey;

	PKH::UI* statPanel = nullptr;
	PKH::UI* mainPanel = nullptr;
	PKH::UI* miniPanel = nullptr;
	PKH::UI* invenPanel = nullptr;
	PKH::UI* faceBorder = nullptr;
	PKH::UI* facePanel = nullptr;
	Label* hpLabel = nullptr;
	Label* mpLabel = nullptr;

	Label* statLabel[8];

	PKH::UI* slotSpell1 = nullptr;
	PKH::UI* slotSpell2 = nullptr;
	PKH::UI* slotSpell3 = nullptr;
	PKH::UI* slotSpell4 = nullptr;
	PKH::UI* slotPassive = nullptr;
	PKH::UI* slotSummoner1 = nullptr;
	PKH::UI* slotSummoner2 = nullptr;

	Champion* champion = nullptr;
};

