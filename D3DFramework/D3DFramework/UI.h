#pragma once
#include "GameObject.h"
#include "Rectangle.h"

namespace PKH
{
    enum class UIType
    {
        DEFAULT,
        PLAYER_INFO,
        MINIMAP,
        SHOP,
        STATUS_INFO,
        CURSOR,
    };

    class UI : public GameObject
    {
    public:
        UI();
        virtual ~UI();

        virtual void Update() override;
        virtual void PostUpdate() override;


        void UpdateEvent();
        void ClearEvent();

        // 이벤트 리스너
        virtual void OnHover();
        virtual void OnLeave();
        virtual void OnLButtonDown();
        virtual void OnLButtonUp();
        virtual void OnRButtonDown();
        virtual void OnRButtonUp();
        virtual void OnClick();
        virtual void OnDoubleClick();
        virtual void OnChangedText();

        Vector3 GetSize();
        Vector3 GetLocation();

        void SetSize(int w, int h);
        void SetSizeByTexture();
        // 좌상단 기준

        void SetLocation(int x, int y);
        void SetLocation(float x, float y);
        void SetLocation(Vector2 pos);
        void SetTexture(const wstring& _key);



    public:
        
        //wstring textureKey;
        Rectangle* mesh = nullptr;
        Texture* texture = nullptr;

        // 텍스트 관련
        wstring text; // 출력할 텍스트 (RW)
        D3DCOLOR foreColor = D3DCOLOR_ARGB(255, 1, 1, 1);
        Vector3 textOffsetPosition;// 텍스트를 출력할 local(offset)위치 (RW) 
        bool textRenderFlag = false;// 텍스트를 출력할 UI인가? (RW)

        // 넓이 높이 (R)
        int width = 0;
        int height = 0;

        UIType type = UIType::DEFAULT;

    public:
        // 이벤트 콜백 (RW)
        void (*Click)() = nullptr;
        void (*DoubleClick)() = nullptr;
        void (*LButtonDown)() = nullptr;
        void (*LButtonUp)() = nullptr;
        void (*RButtonDown)() = nullptr;
        void (*RButtonUp)() = nullptr;
        void (*Hover)() = nullptr;
        void (*Leave)() = nullptr;
        void (*ChangedText)() = nullptr;

    private:
        // 이벤트 관련 
        bool isHover = false;
        bool isLeave = false;
        bool isLButtonDown = false;
        bool isRButtonDown = false;

        bool clickFlag = false;
        float doubleClickTick = 0.f;
        float doubleClickDelay = 0.4f;

        wstring oldText;

    };



}
