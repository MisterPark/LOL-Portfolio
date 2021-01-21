#pragma once
#include "IScene.h"

class Label;
class Champion;

class GameScene :
    public IScene
{
public:
    GameScene();
    // IScene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    void PacketProc(CPacket* pPacket);
    void NetProc();

    void ReqTime();
    void ResTime(CPacket* pack);
    void ResMove(CPacket* pack);

    void CreateEnvironment();
    void CreateChampion();

    Network* net = nullptr;
    Vector3 spawnPos[10];

    Champion* champions[10] = {};
    // 시간측정
    DWORD oldTime = 0;
    float sendTick = 0.f;
    float sendDelay = 1.f;
    Label* latencyLabel = nullptr;
};

