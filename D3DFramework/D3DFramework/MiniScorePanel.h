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

    virtual void Update() override;

    void SetBlueTeamKillScore(int _value);
    void SetRedTeamKillScore(int _value);
    void SetKillScore(int _value);
    void SetDeathScore(int _value);
    void SetAssistScore(int _value);
    void SetMinionScore(int _value);
    void SetTime(int _minute, int _second);

    bool GetSecond(float* _outSec);
    bool GetMinute(int* _outMin);
    bool GetTime(int* _outMin, int* _outSec);

private:
    Label* blueKillLabel = nullptr;
    Label* redKillLabel = nullptr;
    Label* kdaLabel = nullptr;
    Label* minionLabel = nullptr;
    Label* timeLabel = nullptr;

    int kill = 0;
    int death = 0;
    int assist = 0;

    float time = 0.f;
};

