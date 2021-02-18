#pragma once
#include "Panel.h"

class Label;

class MiniScorePanel :
    public Panel
{
public:
    MiniScorePanel();
    virtual ~MiniScorePanel();
public:
    static MiniScorePanel* GetInstance();
    static void DestroyInstance();


    void SetBlueTeamKillScore(int _value);
    void SetRedTeamKillScore(int _value);
    void SetKillScore(int _value);
    void SetDeathScore(int _value);
    void SetAssistScore(int _value);
    void SetMinionScore(int _value);
    void SetTime(int _minute, int _second);

private:
    Label* blueKillLabel = nullptr;
    Label* redKillLabel = nullptr;
    Label* kdaLabel = nullptr;
    Label* minionLabel = nullptr;
    Label* timeLabel = nullptr;

    int kill = 0;
    int death = 0;
    int assist = 0;
};

