#pragma once
#include "Panel.h"

class Label;
class OutlinedSlot;
class AnnouncerPanel :
    public Panel
{
    enum class AnnounceType {
        None, // 단일
        One, // 초상화 1개
        Two, // 초상화 2개
        End
    };

    struct AnnouncerData {
        AnnounceType type;
        std::wstring string;
        std::wstring soundKey;
        Team team;
        std::wstring face1;
        std::wstring face2;
        bool soundPlay = false;
    };

public:
    AnnouncerPanel();
    virtual ~AnnouncerPanel();
public:
    static AnnouncerPanel* GetInstance();
    static void DestroyInstance();

    virtual void Update() override;
    
    void AddAnnouncer(const std::wstring& _str, Team _team, const std::wstring _soundKey);
    void AddAnnouncer(const std::wstring& _str, Team _team, const std::wstring _soundKey, const std::wstring& _face1);
    void AddAnnouncer(const std::wstring& _str, Team _team, const std::wstring _soundKey, const std::wstring& _face1, const std::wstring& _face2);

private:
    list<AnnouncerData> data;
    const float minHoldTime = 2.f;
    const float maxHoldTime = 3.f;
    float tick = 0.f;

    Label* label = nullptr;
    UI* underline = nullptr;

    OutlinedSlot* typeone_face = nullptr;

    OutlinedSlot* typetwoL_face = nullptr;

    OutlinedSlot* typetwoR_face = nullptr;

};

