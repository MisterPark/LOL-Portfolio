#include "stdafx.h"
#include "ScorePanel.h"
#include "Champion.h"
#include "Label.h"
#include "TestScene.h"
ScorePanel* pScorePanel = nullptr;
std::wstring dragonCountTex[(UINT)Dragon::End] = {
	L"scoreboard_dragoncount_wind",
	L"scoreboard_dragoncount_fire",
	L"scoreboard_dragoncount_earth",
	L"scoreboard_dragoncount_water",
	L"scoreboard_dragoncount_break"
};

std::wstring dragonSoulTex1[(UINT)Dragon::End] = {
	L"scoreboard_dragonsimbol_wind_1",
	L"scoreboard_dragonsimbol_fire_1",
	L"scoreboard_dragonsimbol_earth_1",
	L"scoreboard_dragonsimbol_water_1"
};

std::wstring dragonSoulTex2[(UINT)Dragon::End] = {
	L"scoreboard_dragonsimbol_wind_2",
	L"scoreboard_dragonsimbol_fire_2",
	L"scoreboard_dragonsimbol_earth_2",
	L"scoreboard_dragonsimbol_water_2"
};

std::wstring dragonTimeSimbol[(UINT)Dragon::End] = {
	L"scoreboard_simbol_dragon_wind",
	L"scoreboard_simbol_dragon_fire",
	L"scoreboard_simbol_dragon_earth",
	L"scoreboard_simbol_dragon_ocean",
	L"",
	L"scoreboard_simbol_dragon_elder"
};

ScorePanel::ScorePanel()
{
	int screenW = MainGame::GetWidth();
	int screenH = MainGame::GetHeight();

	auto mainpanelTex = RenderManager::GetTexture(L"scoreboard_mainpanel");

// 용 시간
	auto mobpanelTex = RenderManager::GetTexture(L"scoreboard_mobtimepanel"); 
	auto heraldpanelTex = RenderManager::GetTexture(L"scoreboard_heraldtimepanel");

	UI* heraldTimePanel = CreateChild(L"scoreboard_heraldtimepanel", Vector2((screenW * 0.5f) - (heraldpanelTex->GetSpriteWidth() * 0.5f), 76.f));
	UI* mobTimePanel    = CreateChild(L"scoreboard_mobtimepanel",    Vector2((screenW * 0.5f) - (mobpanelTex->GetSpriteWidth()    * 0.5f), -4.f));
	
	timeLabel[(UINT)MobTimeID::WestBlue] = mobTimePanel->AddChild<Label>(L"timeWestBlueLabel", new Label());
	timeLabel[(UINT)MobTimeID::WestBlue]->SetLocation(53, 23);
	timeLabel[(UINT)MobTimeID::WestBlue]->SetText(L"%d:%d", 1, 30);
	timeLabel[(UINT)MobTimeID::WestBlue]->SetColor(255, 148, 181, 194);

	timeLabel[(UINT)MobTimeID::SouthRed] = mobTimePanel->AddChild<Label>(L"timeSouthRedLabel", new Label());
	timeLabel[(UINT)MobTimeID::SouthRed]->SetLocation(132, 23);
	timeLabel[(UINT)MobTimeID::SouthRed]->SetText(L"%d:%d", 1, 30);
	timeLabel[(UINT)MobTimeID::SouthRed]->SetColor(255, 194, 147, 148);

	timeLabel[(UINT)MobTimeID::NorthRed] = mobTimePanel->AddChild<Label>(L"timeNorthRedLabel", new Label());
	timeLabel[(UINT)MobTimeID::NorthRed]->SetLocation(411, 23);
	timeLabel[(UINT)MobTimeID::NorthRed]->SetText(L"%d:%d", 1, 30);
	timeLabel[(UINT)MobTimeID::NorthRed]->SetColor(255, 194, 147, 148);

	timeLabel[(UINT)MobTimeID::EastBlue] = mobTimePanel->AddChild<Label>(L"timeEastBlueLabel", new Label());
	timeLabel[(UINT)MobTimeID::EastBlue]->SetLocation(489, 23);
	timeLabel[(UINT)MobTimeID::EastBlue]->SetText(L"%d:%d", 1, 30);
	timeLabel[(UINT)MobTimeID::EastBlue]->SetColor(255, 148, 181, 194);

	timeLabel[(UINT)MobTimeID::Dragon] = mobTimePanel->AddChild<Label>(L"timeDragonLabel", new Label());
	timeLabel[(UINT)MobTimeID::Dragon]->SetLocation(319, 23);
	timeLabel[(UINT)MobTimeID::Dragon]->SetText(L"%d:%d", 1, 30);
	timeLabel[(UINT)MobTimeID::Dragon]->SetColor(255, 199, 173, 150);

	timeLabel[(UINT)MobTimeID::Baron] = mobTimePanel->AddChild<Label>(L"timeBaronLabel", new Label());
	timeLabel[(UINT)MobTimeID::Baron]->SetLocation(224, 23);
	timeLabel[(UINT)MobTimeID::Baron]->SetText(L"%d:%d", 1, 30);
	timeLabel[(UINT)MobTimeID::Baron]->SetColor(255, 188, 152, 195);

	timeLabel[(UINT)MobTimeID::Herald] = heraldTimePanel->AddChild<Label>(L"timeHeraldLabel", new Label());
	timeLabel[(UINT)MobTimeID::Herald]->SetLocation(93, 17);
	timeLabel[(UINT)MobTimeID::Herald]->SetText(L"%d:%d", 1, 30);
	timeLabel[(UINT)MobTimeID::Herald]->SetColor(255, 188, 152, 195);

	for (int i = 0; i < (UINT)MobTimeID::End; ++i) {
		timeLabel[i]->align = Label::Align::Center;
		timeLabel[i]->valign = Label::VAlign::Middle;
	}

	simbolBig[(UINT)MobTimeID::WestBlue] = mobTimePanel->AddChild<UI>(L"simbolBigWestBlue",  new UI(L"scoreboard_simbol_blue", Vector2(25, 10)));
	simbolBig[(UINT)MobTimeID::SouthRed] = mobTimePanel->AddChild<UI>(L"simbolBigSouthRed",  new UI(L"scoreboard_simbol_red", Vector2(100, 10)));
	simbolBig[(UINT)MobTimeID::NorthRed] = mobTimePanel->AddChild<UI>(L"simbolBigNorthRed",  new UI(L"scoreboard_simbol_red", Vector2(379, 10)));
	simbolBig[(UINT)MobTimeID::EastBlue] = mobTimePanel->AddChild<UI>(L"simbolBigEastBlue",  new UI(L"scoreboard_simbol_blue", Vector2(461, 10)));
	simbolBig[(UINT)MobTimeID::Dragon]   = mobTimePanel->AddChild<UI>(L"simbolBigDragon",    new UI(L"", Vector2(0, 0)));
	simbolBig[(UINT)MobTimeID::Baron]    = mobTimePanel->AddChild<UI>(L"simbolBigBaron",     new UI(L"scoreboard_simbol_baron", Vector2(183, 10)));
	simbolBig[(UINT)MobTimeID::Herald]   = heraldTimePanel->AddChild<UI>(L"simbolBigHerald", new UI(L"scoreboard_simbol_riftherald", Vector2(66, 2)));

	simbolSmall[(UINT)MobTimeID::WestBlue] = mobTimePanel->AddChild<UI>(L"simbolBigWestBlue", new UI(L"scoreboard_simbol_blue", Vector2(39, 36)));
	simbolSmall[(UINT)MobTimeID::SouthRed] = mobTimePanel->AddChild<UI>(L"simbolBigSouthRed", new UI(L"scoreboard_simbol_red", Vector2(114, 36)));
	simbolSmall[(UINT)MobTimeID::NorthRed] = mobTimePanel->AddChild<UI>(L"simbolBigNorthRed", new UI(L"scoreboard_simbol_red", Vector2(395, 36)));
	simbolSmall[(UINT)MobTimeID::EastBlue] = mobTimePanel->AddChild<UI>(L"simbolBigEastBlue", new UI(L"scoreboard_simbol_blue", Vector2(475, 36)));
	simbolSmall[(UINT)MobTimeID::Dragon] = mobTimePanel->AddChild<UI>(L"simbolBigDragon", new UI(L"", Vector2(0, 0)));
	simbolSmall[(UINT)MobTimeID::Baron] = mobTimePanel->AddChild<UI>(L"simbolBigBaron", new UI(L"scoreboard_simbol_baron", Vector2(204, 40)));
	simbolSmall[(UINT)MobTimeID::Herald] = heraldTimePanel->AddChild<UI>(L"simbolBigHerald", new UI(L"scoreboard_simbol_riftherald", Vector2(80, 27)));
	for (int i = 0; i < (UINT)MobTimeID::End; ++i)
	{
		simbolSmall[i]->transform->scale = { 0.5f, 0.5f, 1.f };
	}

// 메인
	UI* mainPanel = CreateChild(L"scoreboard_mainpanel", Vector2((screenW * 0.5f) - (mainpanelTex->GetSpriteWidth() * 0.5f), (screenH * 0.5f) - (mainpanelTex->GetSpriteHeight() * 0.5f)));

// 용
	dragonSoulUI = mainPanel->CreateChild(L"scoreboard_dragonsimbol_default", Vector2(460, 10));
	dragonSoulUI->transform->scale = { 0.75f, 0.75f, 0.75f };

	// 용 카운트
	for (int i = 0; i < 4; ++i) {
		dragonCountUI[(UINT)Team::BLUE][i] = mainPanel->CreateChild(L"", Vector2(400 - (46 * i), 20));
		dragonCountUI[(UINT)Team::BLUE][i]->transform->scale = { 0.75f, 0.75f, 0.75f };

		dragonCountUI[(UINT)Team::RED][i] = mainPanel->CreateChild(L"", Vector2(543 + (46 * i), 20));
		dragonCountUI[(UINT)Team::RED][i]->transform->scale = { 0.75f, 0.75f, 0.75f };
	}

	// 용추가 예시
	// 한 팀이 4개가 되면 자동으로 나머지 빈 자리는 부셔지는 아이콘이 들어감
	//AddDragon(Dragon::INFERNAL, Team::BLUE);
	//AddDragon(Dragon::OCEAN, Team::RED);
	//AddDragon(Dragon::OCEAN, Team::RED);
	//SetDragonSoul(Dragon::OCEAN); // 3용 이후 용 결정될 때 호출
	//AddDragon(Dragon::OCEAN, Team::RED);
	//AddDragon(Dragon::OCEAN, Team::RED);
	//SetDragonSoulBuf(); // 4용 버프 적용될 때 호출
	
// 라벨
	turretCountLabel[(UINT)Team::BLUE] = new Label(15);
	mainPanel->AddChild<Label>(L"BlueTurretCount", turretCountLabel[(UINT)Team::BLUE]);
	turretCountLabel[(UINT)Team::BLUE]->SetLocation(381, 91);
	turretCountLabel[(UINT)Team::BLUE]->SetText(publicScore[(int)PublicScoreID::BlueTeamTurretKillScore]);
	turretCountLabel[(UINT)Team::BLUE]->align = Label::Align::Right;
	turretCountLabel[(UINT)Team::BLUE]->valign = Label::VAlign::Middle;
	turretCountLabel[(UINT)Team::BLUE]->SetColor(255, 78, 157, 222);

	turretCountLabel[(UINT)Team::RED] = new Label(15);
	mainPanel->AddChild<Label>(L"RedTurretCount", turretCountLabel[(UINT)Team::RED]);
	turretCountLabel[(UINT)Team::RED]->SetLocation(588, 91);
	turretCountLabel[(UINT)Team::RED]->SetText(publicScore[(int)PublicScoreID::RedTeamTurretKillScore]);
	turretCountLabel[(UINT)Team::RED]->align = Label::Align::Left;
	turretCountLabel[(UINT)Team::RED]->valign = Label::VAlign::Middle;
	turretCountLabel[(UINT)Team::RED]->SetColor(255, 223, 60, 50);

	killCountLabel[(UINT)Team::BLUE] = new Label(20);
	mainPanel->AddChild<Label>(L"BlueKillCount", killCountLabel[(UINT)Team::BLUE]);
	killCountLabel[(UINT)Team::BLUE]->SetLocation(466, 91);
	killCountLabel[(UINT)Team::BLUE]->SetText(publicScore[(int)PublicScoreID::BlueTeamKillScore]);
	killCountLabel[(UINT)Team::BLUE]->align = Label::Align::Right;
	killCountLabel[(UINT)Team::BLUE]->valign = Label::VAlign::Middle;
	killCountLabel[(UINT)Team::BLUE]->SetColor(255, 78, 157, 222);

	killCountLabel[(UINT)Team::RED] = new Label(20);
	mainPanel->AddChild<Label>(L"RedKillCount", killCountLabel[(UINT)Team::RED]);
	killCountLabel[(UINT)Team::RED]->SetLocation(497, 91);
	killCountLabel[(UINT)Team::RED]->SetText(publicScore[(int)PublicScoreID::RedTeamKillScore]);
	killCountLabel[(UINT)Team::RED]->align = Label::Align::Left;
	killCountLabel[(UINT)Team::RED]->valign = Label::VAlign::Middle;
	killCountLabel[(UINT)Team::RED]->SetColor(255, 223, 60, 50);

// 챔피언 정보
	for (int i = (UINT)Team::BLUE; i <= (UINT)Team::RED; ++i) {
		for (int j = 0; j < 5; ++j) {
			championScoreUI[i].push_back(mainPanel->CreateChild(L"Champion", Vector2(9 + (475 * (i - (UINT)Team::BLUE)), 120 + (63 * j))));
			UI* champPanel = championScoreUI[i][j];

			// 배경
			champPanel->CreateChild(L"scoreboard_dead", Vector2(0, 2));
			champPanel->CreateChild(L"scoreboard_playermark", Vector2(0, 3));
			champPanel->CreateChild(L"scoreboard_mia", Vector2(6, 3));

			Label* DeadCount = new Label(20);
			champPanel->AddChild<Label>(L"DeadCount", DeadCount);
			DeadCount->SetLocation(15, 29);
			DeadCount->SetText(40);
			DeadCount->align = Label::Align::Center;
			DeadCount->valign = Label::VAlign::Middle;
			DeadCount->SetColor(255, 255, 0, 0);

			// 챔피언 초상화
			UI* portrait = champPanel->CreateChild(L"Portrait", Vector2(80, 10));
			portrait->transform->scale = { 0.35f, 0.35f, 1.f };

			// 챔피언 초상화 테두리
			champPanel->AddChild<UI>(L"ChampBorder", new UI(L"", Vector2(76, 10)));

			// 레벨
			Label* levelLabel = champPanel->AddChild<Label>(L"LevelLabel", new Label(12));
			levelLabel->SetLocation(115, 47);
			levelLabel->SetText(18);
			levelLabel->align = Label::Align::Center;
			levelLabel->valign = Label::VAlign::Middle;

			// 소환사 주문
			UI* spell1 = champPanel->CreateChild(L"summoner_heal", Vector2(45, 11));
			UI* spell2 = champPanel->CreateChild(L"summoner_flash", Vector2(45, 34));
			spell1->transform->scale = { 0.3125f, 0.3125f, 1.f };
			spell2->transform->scale = { 0.3125f, 0.3125f, 1.f };

			// cs
			Label* csLabel = champPanel->AddChild<Label>(L"CSLabel", new Label(12));
			csLabel->SetLocation(156, 29);
			csLabel->SetText(0);
			csLabel->align = Label::Align::Center;
			csLabel->valign = Label::VAlign::Middle;

			// KDA
			Label* kdaLabel = champPanel->AddChild<Label>(L"KDALabel", new Label(12));
			kdaLabel->SetLocation(219, 29);
			kdaLabel->SetText(L"%d//%d//%d", 0, 0, 0);
			kdaLabel->align = Label::Align::Center;
			kdaLabel->valign = Label::VAlign::Middle;

			// 닉네임
			Label* nameLabel = champPanel->AddChild<Label>(L"NameLabel", new Label(12));
			nameLabel->SetLocation(262, 11);
			//nameLabel->SetText(L"박경훈봇");
			nameLabel->align = Label::Align::Left;
			nameLabel->valign = Label::VAlign::Middle;

			// 아이템
			for (int k = 0; k < 7; ++k)
			{
				championItemUI[i][j][k] = champPanel->AddChild<UI>(L"item", new UI(L"scoreboard_itemempty", Vector2(260 + (29 * k), 29)));
				championItemUI[i][j][k]->transform->scale = { 0.4218f, 0.4218f, 1.f };
			}

			championScoreUI[i][j]->Hide();
		}
	}

	// 몹 시간 설정 샘플
	//SetMobTime(MobTimeID::WestBlue, 90.f);
	//SetMobTime(MobTimeID::SouthRed, 90.f);
	//SetMobTime(MobTimeID::NorthRed, 90.f);
	//SetMobTime(MobTimeID::EastBlue, 90.f);
	SetDragonTime(300.f, Dragon::Fire);
	SetMobTime(MobTimeID::Baron, 1200.f);
	SetMobTime(MobTimeID::Herald, 480.f);
}

ScorePanel::~ScorePanel()
{
}

ScorePanel* ScorePanel::GetInstance()
{
	if (pScorePanel == nullptr)
	{
		pScorePanel = new ScorePanel();
	}
	return pScorePanel;
}

void ScorePanel::DestroyInstance()
{
	if (pScorePanel)
	{
		delete pScorePanel;
		pScorePanel = nullptr;
	}
}

void ScorePanel::Update()
{
	if (Input::GetKeyDown('O'))
	{
		visible = !visible;
		visible ? Show() : Hide();
	}

	// 용시간 업데이트
	for (int i = 0; i < (UINT)MobTimeID::End; ++i)
	{
		if (mobTime[i] > 0) mobTime[i] -= Time::DeltaTime();
	}

	// ScorePanel이 활성화 상태일 때
	if (visible)
	{
		for (int i = (UINT)Team::BLUE; i <= (UINT)Team::RED; ++i) {
			size_t j;
			for (j = 0; j < championInfo[i].size(); j++)
			{
				auto* ui = championScoreUI[i][j];
				auto* champ = championInfo[i][j];

				// 사망 표시
				if (champ->IsDead())	ui->children[L"scoreboard_dead"]->Show();
				else					ui->children[L"scoreboard_dead"]->Hide();

				// 사망 카운트
				ui->children[L"DeadCount"]->Hide();

				// 미아 표시
				ui->children[L"scoreboard_mia"]->Hide();

				// 챔피언 초상화 테두리
				if (champ->IsDead())
					dynamic_cast<UI*>(ui->children[L"ChampBorder"])->SetTexture(L"scoreboard_champborder_dead");
				else
					dynamic_cast<UI*>(ui->children[L"ChampBorder"])->SetTexture(L"scoreboard_champborder_alive");
			
				// 레벨
				dynamic_cast<Label*>(ui->children[L"LevelLabel"])->SetText((int)champ->stat->GetValue(StatType::Level));

				// CS
				dynamic_cast<Label*>(ui->children[L"CSLabel"])->SetText((int)champ->stat->GetValue(StatType::MinionKilled));

				// KDA
				int killScore = (int)champ->stat->GetValue(StatType::KillScore);
				int deathScore = (int)champ->stat->GetValue(StatType::DeathScore);
				int assistScore = (int)champ->stat->GetValue(StatType::AssistScore);
				dynamic_cast<Label*>(ui->children[L"KDALabel"])->SetText(L"%d/%d/%d", killScore, deathScore, assistScore);

				// 아이템
				for (int k = 0; k < 7; k++)
				{
					auto item = champ->inventory.GetItem(k);
					if (item == nullptr) championItemUI[i][j][k]->SetTexture(L"scoreboard_itemempty");
					else                 championItemUI[i][j][k]->SetTexture(item->GetIcon());
				}

			}
			for (; j < 5; j++)
			{
				championScoreUI[i][j]->Hide();
			}
		}
		// 정글몹 타이머
		TestScene* scene = dynamic_cast<TestScene*>(SceneManager::GetCurrentScene());
		if (scene != nullptr)
		{
			int j = 0;
			for (int i = (int)UnitID::Red1; i <= (int)UnitID::Blue2; i++)
			{
				Unit* mob = scene->unitMap.find(i)->second;
				if (mob->IsDead())
					mobTime[j] = mob->GetRemainingRespawnTime();
				j++;
			}
		}
		// 용시간
		for (int i = 0; i < (UINT)MobTimeID::End; ++i)
		{
			int m = (int)mobTime[i] / 60;
			int s = (int)mobTime[i] % 60;
			timeLabel[i]->SetText(L"%d:%d", m, s);

			if (mobTime[i] <= 1) {
				simbolBig[i]->Show();
				timeLabel[i]->Hide();
				simbolSmall[i]->Hide();
			}
			else {
				timeLabel[i]->Show();
				simbolSmall[i]->Show();
				simbolBig[i]->Hide();
			}
		}
		// 팀의 타워 킬수
		turretCountLabel[(UINT)Team::BLUE]->SetText(publicScore[(int)PublicScoreID::BlueTeamTurretKillScore]);
		turretCountLabel[(UINT)Team::RED]->SetText(publicScore[(int)PublicScoreID::RedTeamTurretKillScore]);
		// 팀의 킬수
		int aa = publicScore[(int)PublicScoreID::BlueTeamKillScore];
		int bb = publicScore[(int)PublicScoreID::RedTeamKillScore];
		int cc = ScorePanel::GetInstance()->GetPublicScore(PublicScoreID::BlueTeamKillScore);
		killCountLabel[(UINT)Team::BLUE]->SetText(publicScore[(int)PublicScoreID::BlueTeamKillScore]);
		killCountLabel[(UINT)Team::RED]->SetText(publicScore[(int)PublicScoreID::RedTeamKillScore]);
	}
}

void ScorePanel::AddChampion(Champion* _champ, bool _isPlayer/* = false*/)
{
	// 5인
	if (championInfo[(UINT)_champ->GetTeam()].size() >= 5) return;
	
	// 중복 확인
	for (auto Champ : championInfo[(UINT)_champ->GetTeam()]) {
		if (Champ->GetID() == _champ->GetID()) return;
	}

	UINT index = championInfo[(UINT)_champ->GetTeam()].size();

	championInfo[(UINT)_champ->GetTeam()].push_back(_champ);

	UI* ui = championScoreUI[(UINT)_champ->GetTeam()][index];

	dynamic_cast<UI*>(ui->children[L"Portrait"])->SetTexture(_champ->faceCircleTexkey);
	dynamic_cast<Label*>(ui->children[L"NameLabel"])->SetText(_champ->nickname);

	if (_isPlayer) {

	}
	else {
		ui->DeleteChild(L"scoreboard_playermark");
	}
}

void ScorePanel::AddDragon(Dragon _dragon, Team _team)
{
	int size = dragonCount[(UINT)_team].size();
	int index = size;
	if (size == 4) return;

	dragonCount[(UINT)_team].push_back(_dragon);
	dragonCountUI[(UINT)_team][index]->SetTexture(dragonCountTex[(UINT)_dragon]);

	if (index == 3) {
		for (int i = dragonCount[(UINT)Team::BLUE].size(); i < 4; ++i)
			dragonCountUI[(UINT)Team::BLUE][i]->SetTexture(dragonCountTex[(UINT)Dragon::Break]);
		for (int i = dragonCount[(UINT)Team::RED].size(); i < 4; ++i)
			dragonCountUI[(UINT)Team::RED][i]->SetTexture(dragonCountTex[(UINT)Dragon::Break]);
	}
}

void ScorePanel::SetDragonSoul(Dragon _dragon)
{
	dragonSoulUI->SetTexture(dragonSoulTex1[(UINT)_dragon]);
	dragonSoul = _dragon;
}

void ScorePanel::SetDragonSoulBuf()
{
	dragonSoulUI->SetTexture(dragonSoulTex2[(UINT)dragonSoul]);
}

void ScorePanel::SetMobTime(MobTimeID _mob, float _time)
{
	mobTime[(UINT)_mob] = _time;
}

void ScorePanel::SetDragonTime(float _time, Dragon _dragon)
{
	mobTime[(UINT)MobTimeID::Dragon] = _time;

	// 드래곤 심볼 센터
	// 319, 31 - Big
	// 319, 52 - Small

	simbolBig[(UINT)MobTimeID::Dragon]->SetTexture(dragonTimeSimbol[(UINT)_dragon]);
	simbolSmall[(UINT)MobTimeID::Dragon]->SetTexture(dragonTimeSimbol[(UINT)_dragon]);

	Vector2 sizeBig = simbolBig[(UINT)MobTimeID::Dragon]->GetSize();
	Vector2 sizeSmall = simbolSmall[(UINT)MobTimeID::Dragon]->GetSize();

	simbolBig[(UINT)MobTimeID::Dragon]->SetLocation(319 - (sizeBig.x * 0.5f), 38 - (sizeBig.y * 0.5f));
	simbolSmall[(UINT)MobTimeID::Dragon]->SetLocation(319 - (sizeSmall.x * 0.5f), 52 - (sizeSmall.y * 0.5f));
}

void ScorePanel::Show()
{
	GameObject::Show();

	for (int i = 0; i < (UINT)MobTimeID::End; ++i)
	{
		if (mobTime[i] < 0) {
			timeLabel[i]->Hide();
			simbolSmall[i]->Hide();
		} else {
			simbolBig[i]->Hide();
		}
	}
}

void ScorePanel::Hide()
{
	GameObject::Hide();
}
