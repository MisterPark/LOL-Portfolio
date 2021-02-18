#pragma once
#include "GameObject.h"
#include "Rectangle.h"

namespace PKH
{

    class UI : public GameObject
    {
    public:
        UI();
        UI(const Vector2& pos);
        UI(const std::wstring& _tag, const Vector2& pos);
        virtual ~UI();

        virtual void Initialize() override;
        virtual void Release() override;
        virtual void Update() override;


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

        Vector2 GetSize();
        Vector2 GetLocation();

        void SetSize(int w, int h);
        void SetSizeByTexture();
        // 좌상단 기준

        void SetLocation(int x, int y);
        void SetLocation(float x, float y);
        void SetLocation(Vector2 pos);
        void SetTexture(const wstring& _key);

        // child
        UI* AddChild(UI* _ui);
        UI* AddChild(const std::wstring& _tag, const Vector2& _pos);

        bool Intersect(Vector2 _target);
        RECT GetRect();
        Texture* GetTexture();

        void BringToTop();

    public:

        Rectangle* mesh = nullptr;
        Texture* texture = nullptr;
        Vector2 uvRatio = { 1,1 };
        // 넓이 높이 (R)
        Vector2 size;

        std::wstring tag;
    public:
        // 이벤트 (RW)
        Event Click;
        Event DoubleClick;
        Event LButtonDown;
        Event LButtonUp;
        Event RButtonDown;
        Event RButtonUp;
        Event Hover;
        Event Leave;
        Event ChangedText;

    private:
        // 이벤트 관련 
        bool isHover = false;
        bool isLeave = false;
        bool isLButtonDown = false;
        bool isRButtonDown = false;

        bool clickFlag = false;
        float doubleClickTick = 0.f;
        float doubleClickDelay = 0.4f;


    };



}
