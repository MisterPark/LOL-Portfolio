#include "stdafx.h"
#include "MiniScorePanel.h"
#include "Label.h"
#include "Tooltip.h"
#include <sstream>

MiniScorePanel* self = nullptr;

MiniScorePanel::MiniScorePanel()
{
	int screenW = MainGame::GetWidth();
	int screenH = MainGame::GetHeight();

	// 패널
	Panel* panel = new Panel();
	panel->SetTexture(L"panel (4)");
	panel->SetSize(428, 32);
	Vector2 size = panel->GetSize();
	AddChild(L"Panel", panel);

	// 부모 위치 설정
	SetLocation(screenW - size.x, 0.f);

	Panel* vs = new Panel();
	vs->SetTexture(L"hud_icon (1)");
	vs->SetLocation(85.f, 5.f);
	AddChild(L"vs", vs);
	vs->Hover += Engine::Handler(this, &MiniScorePanel::ShowTooltipKill);
	vs->Leave += Engine::Handler(this, &MiniScorePanel::HideTooltipKill);

	Panel* sword = new Panel();
	sword->SetTexture(L"hud_icon (2)");
	sword->SetLocation(158.f, 5.f);
	AddChild(L"sword", sword);

	Panel* minion = new Panel();
	minion->SetTexture(L"hud_icon (4)");
	minion->SetLocation(271.f, 5.f);
	AddChild(L"minion", minion);

	Panel* time = new Panel();
	time->SetTexture(L"hud_icon (3)");
	time->SetLocation(345.f, 5.f);
	AddChild(L"time", time);

	blueKillLabel = new Label(25);
	redKillLabel = new Label(25);
	kdaLabel = new Label();
	minionLabel = new Label();
	timeLabel = new Label();

	blueKillLabel->align = Label::Align::Right;
	
	blueKillLabel->SetColor(255, 81, 162, 230);
	redKillLabel->SetColor(255, 232, 61, 50);

	blueKillLabel->SetLocation(85.f, 5.f);
	redKillLabel->SetLocation(110.f, 5.f);
	kdaLabel->SetLocation(180.f, 5.f);
	minionLabel->SetLocation(295.f, 5.f);
	timeLabel->SetLocation(369.f, 5.f);

	blueKillLabel->SetText(0);
	redKillLabel->SetText(0);
	kdaLabel->SetText(L"%d/%d/%d", 0, 0, 0);
	minionLabel->SetText(0);
	timeLabel->SetText(L"%02d:%02d", 0, 0);

	AddChild(L"blueKillLabel", blueKillLabel);
	AddChild(L"redKillLabel", redKillLabel);
	AddChild(L"kdaLabel", kdaLabel);
	AddChild(L"minionLabel", minionLabel);
	AddChild(L"timeLabel", timeLabel);

	kdaLabel->Hover += Engine::Handler(this, &MiniScorePanel::ShowTooltipKda);
	kdaLabel->Leave += Engine::Handler(this, &MiniScorePanel::HideTooltipKda);

	minionLabel->Hover += Engine::Handler(this, &MiniScorePanel::ShowTooltipMinion);
	minionLabel->Leave += Engine::Handler(this, &MiniScorePanel::HideTooltipMinion);

}

MiniScorePanel::~MiniScorePanel()
{
}

MiniScorePanel* MiniScorePanel::GetInstance()
{
	if (self == nullptr)
	{
		self = new MiniScorePanel();
	}
	return self;
}

void MiniScorePanel::DestroyInstance()
{
	Safe_Delete(&self);
}

void MiniScorePanel::Update()
{
	float dt = Time::DeltaTime();

	time += dt;

	int second = (int)time;
	int minute = 0;
	if (second != 0)
	{
		minute = second / 60;
	}
	second = (int)fmodf(time, 60.f);

	timeLabel->SetText(L"%02d:%02d", minute, second);

	Panel::Update();
}

void MiniScorePanel::SetBlueTeamKillScore(int _value)
{
	blueKillLabel->SetText(_value);
}

void MiniScorePanel::SetRedTeamKillScore(int _value)
{
	redKillLabel->SetText(_value);
}

void MiniScorePanel::SetKillScore(int _value)
{
	kill = _value;

	kdaLabel->SetText(L"%d/%d/%d", kill, death, assist);
}

void MiniScorePanel::SetDeathScore(int _value)
{
	death = _value;

	kdaLabel->SetText(L"%d/%d/%d", kill, death, assist);
}

void MiniScorePanel::SetAssistScore(int _value)
{
	assist = _value;

	kdaLabel->SetText(L"%d/%d/%d", kill, death, assist);
}

void MiniScorePanel::SetMinionScore(int _value)
{
	minionLabel->SetText(_value);
}

void MiniScorePanel::SetTime(int _minute, int _second)
{
	time = (float)(_minute * 60 + _second);
}

bool MiniScorePanel::GetSecond(float* _outSec)
{
	if (_outSec == nullptr) return false;

	*_outSec = time;

	return true;
}

bool MiniScorePanel::GetMinute(int* _outMin)
{
	if (_outMin == nullptr) return false;

	*_outMin = (((int)time) / 60);

	return true;
}

bool MiniScorePanel::GetTime(int* _outMin, int* _outSec)
{
	if (_outMin == nullptr) return false;
	if (_outSec == nullptr) return false;

	*_outSec = (int)fmodf(time, 60.f);
	*_outMin = (((int)time) / 60);

	return true;
}

void MiniScorePanel::ShowTooltipKill(GameObject* sender, MouseEventArg* args)
{
	Tooltip* tooltip = nullptr;

	auto iter = sender->children.find(L"tooltip");
	if (sender->children.end() == iter) {
		iter = sender->children.emplace(L"tooltip", nullptr).first;
	}

	iter->second = tooltip = new Tooltip(L"팀 전체 킬 수");

	Vector3 cursorPos = Cursor::GetMousePos();
	tooltip->SetLocation(cursorPos.x, cursorPos.y + 50);
	tooltip->Show();
}

void MiniScorePanel::HideTooltipKill(GameObject* sender, MouseEventArg* args)
{
	auto iter = sender->children.find(L"tooltip");
	if (sender->children.end() == iter) return;

	delete iter->second;
	iter->second = nullptr;
}

void MiniScorePanel::ShowTooltipKda(GameObject* sender, MouseEventArg* args)
{
	Tooltip* tooltip = nullptr;

	auto iter = sender->children.find(L"tooltip");
	if (sender->children.end() == iter) {
		iter = sender->children.emplace(L"tooltip", nullptr).first;
	}

	iter->second = tooltip = new Tooltip(L"킬/데스/어시스트");

	Vector3 cursorPos = Cursor::GetMousePos();
	tooltip->SetLocation(cursorPos.x, cursorPos.y + 50);
	tooltip->Show();
}

void MiniScorePanel::HideTooltipKda(GameObject* sender, MouseEventArg* args)
{
	auto iter = sender->children.find(L"tooltip");
	if (sender->children.end() == iter) return;

	delete iter->second;
	iter->second = nullptr;
}

void MiniScorePanel::ShowTooltipMinion(GameObject* sender, MouseEventArg* args)
{
	Tooltip* tooltip = nullptr;

	auto iter = sender->children.find(L"tooltip");
	if (sender->children.end() == iter) {
		iter = sender->children.emplace(L"tooltip", nullptr).first;
	}

	iter->second = tooltip = new Tooltip(L"미니언 처치");

	Vector3 cursorPos = Cursor::GetMousePos();
	tooltip->SetLocation(cursorPos.x, cursorPos.y + 50);
	tooltip->Show();
}

void MiniScorePanel::HideTooltipMinion(GameObject* sender, MouseEventArg* args)
{
	auto iter = sender->children.find(L"tooltip");
	if (sender->children.end() == iter) return;

	delete iter->second;
	iter->second = nullptr;
}
