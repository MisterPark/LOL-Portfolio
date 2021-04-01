#include "stdafx.h"
#include "PlayerInfoPanel.h"
#include "Rectangle.h"
#include "UI.h"
#include "Champion.h"
#include "ItemshopPanel.h"
// Control
#include "Label.h"
#include "OutlinedSlot.h"
#include "Button.h"

PlayerInfoPanel* pPlayerInfoPanel = nullptr;

PlayerInfoPanel::PlayerInfoPanel()
{
    screenW = MainGame::GetWidth();
    screenH = MainGame::GetHeight();

// this
    Texture* mainPanelTex = RenderManager::GetTexture(L"panel (5)");
    this->SetLocation((screenW * 0.5f) - mainPanelTex->GetSpriteWidth() * 0.5f, (float)(screenH - mainPanelTex->GetSpriteHeight()));

// StatPanel
    statPanel = AddChild<UI>(L"statPanel", new UI(L"stat_panel (5)_icon", Vector2(-293, 21)));
    
    int statstartx = 45;
    int statstarty = 31;
    int statinvx = 105;
    int statinvy = 33;
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 2; ++x) {
            int index = x + y * 2;
			statLabel[index] = statPanel->AddChild<Label>(L"stat", new Label(18));

            statLabel[index]->SetText(0);
            statLabel[index]->SetLocation(Vector2(statstartx + statinvx * x, statstarty + statinvy * y));
            statLabel[index]->align = Label::Align::Left;
            statLabel[index]->valign = Label::VAlign::Middle;
            statLabel[index]->SetColor(255, 255, 255, 255);
            
        }
    }

// InvenPanel
	auto recallIcon = AddChild<UI>(L"recallIcon", new UI(L"icon_spell_summonerspell_recall_01", Vector2(734, 88)));
	recallIcon->transform->scale = { 0.6f, 0.6f, 1.f };

    invenPanel = AddChild<UI>(L"invenPanel", new UI(L"panel (2)", Vector2(558, 6)));
	slotRecall = invenPanel->AddChild<OutlinedSlot>(L"recallSlot", new OutlinedSlot(L"border_skill (6)", Vector2(176, 82)));
	
	itemshopBtn = invenPanel->AddChild<Button>(L"itemsshopBtn", new Button(L"button_gold (2)", Vector2(16, 130)));
    itemshopBtn->SetTextureDisable(L"button_gold (1)");
    itemshopBtn->SetTextureHover(L"button_gold (3)");
    itemshopBtn->SetTexturePressed(L"button_gold (4)");
    itemshopBtn->Click += Engine::Handler(&ItemshopPanel::ToggleVisible);
	itemshopBtn->SetText(L"1000");
	itemshopBtn->SetLabelSize(18);
	itemshopBtn->SetLabelPosition(Vector2(127, 16));
	itemshopBtn->SetLabelAlign(Label::Align::Center);
	itemshopBtn->SetLabelVAlign(Label::VAlign::Middle);
	itemshopBtn->SetLabelColor(D3DCOLOR_ARGB(255, 236, 229, 142));

	// 인벤토리
	for (int i = 0; i < 6; i++)
	{
		slotItem[i] = invenPanel->AddChild<OutlinedSlot>(L"slotItem", new OutlinedSlot(L"item_outline", Vector2(16 + (52 * (i % 3)), 27 + (53 * (i / 3 )))));
		slotItem[i]->outline->transform->scale = { 0.67f, 0.67f, 1.f };
		slotItem[i]->icon->transform->scale = { 0.72f, 0.72f, 1.f};
		slotItem[i]->Click += Engine::Handler(this, &PlayerInfoPanel::ClickInventorySlot);
	}

	// 장신구
	slotItem[6] = invenPanel->AddChild<OutlinedSlot>(L"wardSlot", new OutlinedSlot(L"border_skill (5)", Vector2(176, 30))); // 장신구
	slotItem[6]->icon->transform->scale = { 0.6f, 0.6f, 1.f };

	// 인벤토리 선택
	for (int i = 0; i < INVENTORY_MAX; ++i)
	{
		slotItemSelected[i] = invenPanel->AddChild<UI>(L"slotItemSelected", new UI(L"item_outline_selected", Vector2(0, 0)));
	}
	slotItemSelected[0]->SetLocation(16, 27);
	slotItemSelected[1]->SetLocation(68, 27);
	slotItemSelected[2]->SetLocation(120, 27);
	slotItemSelected[3]->SetLocation(16, 80);
	slotItemSelected[4]->SetLocation(68, 80);
	slotItemSelected[5]->SetLocation(120, 80);
	slotItemSelected[6]->SetLocation(176, 30);

	for (int i = 0; i < INVENTORY_MAX - 1; ++i) {
		slotItemSelected[i]->transform->scale = { 0.59f, 0.59f, 1.f };
	}
	slotItemSelected[6]->transform->scale = { 0.49f, 0.49f, 1.f };

	// 인벤토리 단축키 라벨
	Label* itemLabel[INVENTORY_MAX] = { nullptr, };
	for (int i = 0; i < INVENTORY_MAX; ++i)
	{
		itemLabel[i] = invenPanel->AddChild<Label>(L"ItemLabel", new Label(15));
		itemLabel[i]->SetColor(255, 255, 255, 255);
		itemLabel[i]->align = Label::Align::Center;
		itemLabel[i]->valign = Label::VAlign::Middle;
		itemLabel[i]->outline = true;
	}
	itemLabel[6]->SetColor(255, 244, 214, 108);

	itemLabel[0]->SetText(1);
	itemLabel[1]->SetText(2);
	itemLabel[2]->SetText(3);
	itemLabel[3]->SetText(5);
	itemLabel[4]->SetText(6);
	itemLabel[5]->SetText(7);
	itemLabel[6]->SetText(4);

	itemLabel[0]->SetLocation(Vector2(16, 68));
	itemLabel[1]->SetLocation(Vector2(68, 68));
	itemLabel[2]->SetLocation(Vector2(120, 68));
	itemLabel[3]->SetLocation(Vector2(16, 120));
	itemLabel[4]->SetLocation(Vector2(68, 120));
	itemLabel[5]->SetLocation(Vector2(120, 120));
	itemLabel[6]->SetLocation(Vector2(180, 60));

	Label* recallLabel = invenPanel->AddChild<Label>(L"RecallLabel", new Label(15));
	recallLabel->SetText(L"B");
	recallLabel->SetLocation(Vector2(180, 111));
	recallLabel->SetColor(255, 244, 214, 108);
	recallLabel->align = Label::Align::Center;
	recallLabel->valign = Label::VAlign::Middle;
	recallLabel->outline = true;

// mainPanel
    mainPanel = AddChild<UI>(L"mainPanel", new UI(L"panel (5)", Vector2(0, 0)));
    
    // HP Bar, MP Bar
    hpBarBack = mainPanel->AddChild<UI>(L"HPBarBack", new UI(L"bar_big_red", Vector2(74, 123)));
    hpBar     = mainPanel->AddChild<UI>(L"HPBar",     new UI(L"bar_big1",    Vector2(74, 123)));
    mpBar     = mainPanel->AddChild<UI>(L"MPBar",     new UI(L"bar_big2",    Vector2(74, 143)));
    mainPanel->AddChild<UI>(L"HPBarTipL", new UI(L"bar_tip (1)", Vector2(71, 123)));
    mainPanel->AddChild<UI>(L"HPBarTipR", new UI(L"bar_tip (2)", Vector2(534, 123)));
    mainPanel->AddChild<UI>(L"MPBarTipL", new UI(L"bar_tip (1)", Vector2(71, 143)));
	mainPanel->AddChild<UI>(L"MPBarTipR", new UI(L"bar_tip (2)", Vector2(534, 143)));

	auto barTex = RenderManager::GetTexture(L"bar_big1");
    auto markerTex = RenderManager::GetTexture(L"bar_big_marker");
	hpBarMarker = hpBar->AddChild<UI>(L"HPBarMarker", new UI(L"bar_big_marker", Vector2((barTex->GetSpriteWidth()) - (markerTex->GetSpriteWidth() * 0.5f), (barTex->GetSpriteHeight() * 0.5f) - (markerTex->GetSpriteHeight() * 0.5f))));
	mpBarMarker = mpBar->AddChild<UI>(L"MPBarMarker", new UI(L"bar_big_marker", Vector2((barTex->GetSpriteWidth()) - (markerTex->GetSpriteWidth() * 0.5f), (barTex->GetSpriteHeight() * 0.5f) - (markerTex->GetSpriteHeight() * 0.5f))));

    hpLabel = hpBar->AddChild<Label>(L"HPLabel", new Label(18));
	hpLabel->SetLocation(hpBar->GetSize().x * 0.5f, hpBar->GetSize().y * 0.5f);
	hpLabel->SetText(L"%d/%d", 100, 100);
    hpLabel->align = Label::Align::Center;
    hpLabel->valign = Label::VAlign::Middle;
    hpLabel->SetColor(255, 255, 255, 255);

	mpLabel = mpBar->AddChild<Label>(L"MPLabel", new Label(18));
	mpLabel->SetLocation(mpBar->GetSize().x * 0.5f, mpBar->GetSize().y * 0.5f);
	mpLabel->SetText(L"%d/%d", 100, 100);
	mpLabel->align = Label::Align::Center;
	mpLabel->valign = Label::VAlign::Middle;
	mpLabel->SetColor(255, 255, 255, 255);

	hpRegenLabel = hpBar->AddChild<Label>(L"HPLabel", new Label(18));
	hpRegenLabel->SetLocation(hpBar->GetSize().x - 10, hpBar->GetSize().y * 0.5f);
	hpRegenLabel->SetText(L"+%.1f", 1.0f);
	hpRegenLabel->align = Label::Align::Right;
	hpRegenLabel->valign = Label::VAlign::Middle;
	hpRegenLabel->SetColor(255, 255, 255, 255);

	mpRegenLabel = mpBar->AddChild<Label>(L"MPLabel", new Label(18));
	mpRegenLabel->SetLocation(mpBar->GetSize().x - 10, mpBar->GetSize().y * 0.5f);
	mpRegenLabel->SetText(L"+%.1f", 1.0f);
	mpRegenLabel->align = Label::Align::Right;
	mpRegenLabel->valign = Label::VAlign::Middle;
	mpRegenLabel->SetColor(255, 255, 255, 255);

    // Spell
	spellLevelUI.resize(4);
	for (int i = 0; i < 4; ++i) {
		slotSpell[i] = mainPanel->AddChild<OutlinedSlot>(L"Spell", new OutlinedSlot(L"border_skill (1)", Vector2(125 + (74 * i), 30)));
		SpellTimeLabel[i] = slotSpell[i]->AddChild<Label>(L"SpellTimeLabel", new Label());
		SpellTimeLabel[i]->SetLocation(35, 35);
		SpellTimeLabel[i]->align = Label::Align::Center;
		SpellTimeLabel[i]->valign = Label::VAlign::Middle;

		spellLevelUI[i].resize(spellLevelMax[i]);
		int startX = (int)(160 + (74 * i) - ((float)spellLevelMax[i] / 2 * 10));
		for (int j = 0; j < spellLevelMax[i]; ++j)
			spellLevelUI[i][j] = mainPanel->AddChild<UI>(L"spelllevel", new UI(L"skilllevel_off", Vector2(startX + (11 * j), 104)));

		spellLevelUpButton[i] = mainPanel->AddChild<Button>(L"spellLevelUpButton", new Button(L"button_skillup (1)", Vector2(131 + (74 * i), -25)));
		spellLevelUpButton[i]->SetTextureHover(L"button_skillup (2)");
		spellLevelUpButton[i]->SetTexturePressed(L"button_skillup (3)");
		spellLevelUpButton[i]->SetTextureDisable(L"button_skillup (4)");
	}

    slotPassive   = mainPanel->AddChild<OutlinedSlot>(L"SpellP",  new OutlinedSlot(L"border_skill (2)", Vector2(69,  30)));
    slotSummoner1 = mainPanel->AddChild<OutlinedSlot>(L"SpellS1", new OutlinedSlot(L"border_skill (2)", Vector2(432, 30)));
    slotSummoner2 = mainPanel->AddChild<OutlinedSlot>(L"SpellS2", new OutlinedSlot(L"border_skill (2)", Vector2(488, 30)));
    slotPassive->icon->transform->scale = { 0.71f, 0.71f, 0 };
    slotSummoner1->icon->transform->scale = { 0.71f, 0.71f, 0 };
    slotSummoner2->icon->transform->scale = { 0.71f, 0.71f, 0 };

	Label* QLabel = mainPanel->AddChild<Label>(L"QLabel", new Label(18));
	Label* WLabel = mainPanel->AddChild<Label>(L"WLabel", new Label(18));
	Label* ELabel = mainPanel->AddChild<Label>(L"ELabel", new Label(18));
	Label* RLabel = mainPanel->AddChild<Label>(L"RLabel", new Label(18));
	Label* DLabel = mainPanel->AddChild<Label>(L"DLabel", new Label(18));
	Label* FLabel = mainPanel->AddChild<Label>(L"FLabel", new Label(18));
	QLabel->SetLocation(Vector2(129, 96));
	WLabel->SetLocation(Vector2(203, 96));
	ELabel->SetLocation(Vector2(277, 96));
	RLabel->SetLocation(Vector2(351, 96));
	DLabel->SetLocation(Vector2(436, 78));
	FLabel->SetLocation(Vector2(492, 78));
	QLabel->SetText(L"Q");
	WLabel->SetText(L"W");
	ELabel->SetText(L"E");
	RLabel->SetText(L"R");
	DLabel->SetText(L"D");
	FLabel->SetText(L"F");
	QLabel->align = Label::Align::Center;
	WLabel->align = Label::Align::Center;
	ELabel->align = Label::Align::Center;
	RLabel->align = Label::Align::Center;
	DLabel->align = Label::Align::Center;
	FLabel->align = Label::Align::Center;
	QLabel->valign = Label::VAlign::Middle;
	WLabel->valign = Label::VAlign::Middle;
	ELabel->valign = Label::VAlign::Middle;
	RLabel->valign = Label::VAlign::Middle;
	DLabel->valign = Label::VAlign::Middle;
	FLabel->valign = Label::VAlign::Middle;
    QLabel->SetColor(255, 231, 203, 102);
	WLabel->SetColor(255, 231, 203, 102);
	ELabel->SetColor(255, 231, 203, 102);
	RLabel->SetColor(255, 231, 203, 102);
	DLabel->SetColor(255, 231, 203, 102);
	FLabel->SetColor(255, 231, 203, 102);
	QLabel->outline = true;
	WLabel->outline = true;
	ELabel->outline = true;
	RLabel->outline = true;
	DLabel->outline = true;
	FLabel->outline = true;

    spellPointLabel = mainPanel->AddChild<Label>(L"spellPointLabel", new Label());
    spellPointLabel->SetLocation(254, -50);
    spellPointLabel->SetText(L"레벨 업! +%d", 1);
    spellPointLabel->align = Label::Align::Center;
    spellPointLabel->valign = Label::VAlign::Middle;
    spellPointLabel->SetColor(255, 255, 247, 153);
    

    facePanel = mainPanel->AddChild<UI>(L"champFace", new UI(Vector2(-80, 30)));
    expBar = mainPanel->AddChild<UI>(L"expBar", new UI(L"bar_exp", Vector2(14, 21)));
    auto champBorder = mainPanel->AddChild<UI>(L"champBorder", new UI(L"panel (1)", Vector2(-93, 11)));
    levelLabel = champBorder->AddChild<Label>(L"level", new Label(15));
    levelLabel->SetText(L"1");
    levelLabel->SetLocation(112, 137);
    levelLabel->align = Label::Align::Center;
    levelLabel->valign = Label::VAlign::Middle;

	expBar->uvRatioStart.y = 0.0f;

    mainPanel->AddChild<UI>(L"statBtnBorder", new UI(L"stat_panel (4)", Vector2(-107, 86)));
    Button* statBtn1 = mainPanel->AddChild<Button>(L"statBtn1", new Button(L"stat_panel (1)", Vector2(-100, 92)));
    Button* statBtn2 = mainPanel->AddChild<Button>(L"statBtn2", new Button(L"stat_panel (2)", Vector2(-88, 114)));
    Button* statBtn3 = mainPanel->AddChild<Button>(L"statBtn3", new Button(L"stat_panel (3)", Vector2(-57, 131)));
    statBtn1->SetTextureHover(L"stat_panel (1)_hover");
    statBtn1->SetTexturePressed(L"stat_panel (1)_pressed");
    statBtn1->Click += Engine::Handler(this, &PlayerInfoPanel::PlayerPanel_OnClick);
}

PlayerInfoPanel::~PlayerInfoPanel()
{
}

PlayerInfoPanel* PlayerInfoPanel::GetInstance()
{
    if (pPlayerInfoPanel == nullptr)
    {
        pPlayerInfoPanel = new PlayerInfoPanel();
    }
    return pPlayerInfoPanel;
}

void PlayerInfoPanel::DestroyInstance()
{
    if (pPlayerInfoPanel)
    {
        delete pPlayerInfoPanel;
        pPlayerInfoPanel = nullptr;
    }
}

void PlayerInfoPanel::Initialize()
{
}

void PlayerInfoPanel::Release()
{
}

void PlayerInfoPanel::Update()
{
    GameObject::Update();

	if (champion != nullptr) {
		if (champion->IsDead()) facePanel->grayscale = true;
		else					facePanel->grayscale = false;

		// HP Bar
		{
			float hp = champion->stat->GetValue(StatType::Health);
			if (hp < 0) hp = 0;
			float hpMax = champion->stat->GetValue(StatType::MaxHealth);
			hpBar->uvRatioEnd.x = hp / hpMax;
			hpLabel->SetText(L"%d/%d", (int)hp, (int)hpMax);

			if (hpBarBackRatio < hpBar->uvRatioEnd.x) {
				hpBarBackRatio = hpBar->uvRatioEnd.x;
			}

			Vector2 barSize = hpBar->GetSize();
			Vector2 markerSize = hpBarMarker->GetSize();
			hpBarMarker->SetLocation((barSize.x * (hp / hpMax)) - (markerSize.x * 0.5f), (barSize.y * 0.5f) - (markerSize.y * 0.5f));

			hpBarBackRatio = hpBarBackRatio + (0.1f * ((hp / hpMax) - hpBarBackRatio));
			hpBarBack->uvRatioEnd.x = hpBarBackRatio;
		}
		// MP Bar
		{
			float mp = champion->stat->GetValue(StatType::Mana);
			if (mp < 0) mp = 0;
			float mpMax = champion->stat->GetValue(StatType::MaxMana);

			mpBar->uvRatioEnd.x = 1.f;
			mpLabel->SetText(L"%d/%d", (int)mp, (int)mpMax);

			Vector2 barSize = mpBar->GetSize();
			Vector2 markerSize = mpBarMarker->GetSize();
			mpBarMarker->SetLocation((barSize.x * (mp / mpMax)) - (markerSize.x * 0.5f), (barSize.y * 0.5f) - (markerSize.y * 0.5f));
		}

		// Stat
			// HP Regen
		hpRegenLabel->SetText(L"+%0.1f", champion->stat->GetValue(StatType::HealthRegen));
		if (champion->stat->GetValue(StatType::Health) < champion->stat->GetValue(StatType::MaxHealth)) hpRegenLabel->Show();
		else                                                                                            hpRegenLabel->Hide();

		// MP Regen
		mpRegenLabel->SetText(L"+%0.1f", champion->stat->GetValue(StatType::ManaRegen));
		if (champion->stat->GetValue(StatType::Mana) < champion->stat->GetValue(StatType::MaxMana)) mpRegenLabel->Show();
		else                                                                                        mpRegenLabel->Hide();

		statLabel[0]->SetText(L"%d", (int)champion->stat->GetValue(statNum[0]));
		statLabel[1]->SetText(L"%d", (int)champion->stat->GetValue(statNum[1]));
		statLabel[2]->SetText(L"%d", (int)champion->stat->GetValue(statNum[2]));
		statLabel[3]->SetText(L"%d", (int)champion->stat->GetValue(statNum[3]));
		statLabel[4]->SetText(L"%.2f", champion->stat->GetValue(statNum[4]));
		statLabel[5]->SetText(L"%d%%", (int)champion->stat->GetValue(statNum[5]));
		statLabel[6]->SetText(L"%d", (int)champion->stat->GetValue(statNum[6]));
		statLabel[7]->SetText(L"%d", (int)(champion->stat->GetValue(statNum[7]) * 100));

		itemshopBtn->SetText((int)champion->stat->GetValue(StatType::Gold));

		// Level
		levelLabel->SetText(L"%d", champion->stat->GetValue(StatType::Level));

		// exp
		expBar->uvRatioStart.y = 1.f - (champion->stat->GetValue(StatType::Experience) /
			champion->stat->GetValue(StatType::MaxExperience));

		// Spell
		float cooltime;
		float cooltimeinit;

		for (int i = 0; i < 4; i++) {
			cooltime = champion->skillList[(int)spellNum[i]]->GetCooltime();
			cooltimeinit = champion->skillList[(int)spellNum[i]]->GetCooltime_Init();
			slotSpell[i]->SetCooltime(cooltime, cooltimeinit);
			if (cooltime <= 0) {
				SpellTimeLabel[i]->Hide();
				slotSpell[i]->icon->grayscale = false;
				slotSpell[i]->outline->SetTexture(L"border_skill (1)");
			}
			else {
				SpellTimeLabel[i]->Show();
				slotSpell[i]->icon->grayscale = true;
				slotSpell[i]->outline->SetTexture(L"border_skill (3)");
				if (cooltime >= 1)	SpellTimeLabel[i]->SetText(L"%d", (int)cooltime);
				else				SpellTimeLabel[i]->SetText(L"%.1f", cooltime);
			}

		}

		// Item
		for (int i = 0; i < INVENTORY_MAX; ++i) {
			Item* item = champion->inventory.GetItem(i);
			if (item == nullptr) {
				slotItem[i]->Hide();
			}
			else {
				slotItem[i]->SetIcon(item->GetIcon());
				slotItem[i]->Show();
			}

			if (selectedItemIdx == i) slotItemSelected[i]->Show();
			else					  slotItemSelected[i]->Hide();
		}
    }
}
void PlayerInfoPanel::SetTarget(Champion* _target)
{
    champion = _target;
    if (_target == nullptr) return;
    facePanel->SetTexture(champion->faceCircleTexkey);
    
    slotSpell[0]->SetIcon(champion->qTexKey);
    slotSpell[1]->SetIcon(champion->wTexKey);
    slotSpell[2]->SetIcon(champion->eTexKey);
    slotSpell[3]->SetIcon(champion->rTexKey);
    slotPassive->SetIcon(champion->passiveTexKey);
}

void PlayerInfoPanel::PlayerPanel_OnClick(GameObject* sender, MouseEventArg* arg)
{
    ClickStatButton();
}

void PlayerInfoPanel::SellSelectedItem()
{
	if (selectedItemIdx == -1) return;

	champion->SellItem(selectedItemIdx);
	
	Item* item = champion->inventory.GetItem(selectedItemIdx);
	if (item == nullptr) {
		selectedItemIdx = -1;
	}
}

void PlayerInfoPanel::UnselectInventorySlot()
{
	selectedItemIdx = -1;
}

int PlayerInfoPanel::GetSelectedItemIdx()
{
	return selectedItemIdx;
}

void PlayerInfoPanel::ClickInventorySlot(GameObject* sender, MouseEventArg* args)
{
	auto slot = dynamic_cast<OutlinedSlot*>(sender);
	if (slot == nullptr) return;
	if (!ItemshopPanel::GetInstance()->visible) return;

	for (int i = 0; i < INVENTORY_MAX; ++i)
	{
		if (slotItem[i] == slot) {
			selectedItemIdx = i;
			return;
		}
	}
	selectedItemIdx = -1;
}

void PlayerInfoPanel::ClickStatButton()
{
    pPlayerInfoPanel->statPanel->visible ? 
    pPlayerInfoPanel->statPanel->Hide() :
    pPlayerInfoPanel->statPanel->Show();
}
