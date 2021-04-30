﻿#pragma once
#include "GameObject.h"
#include "Rectangle.h"

class Label;

namespace Engine
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
        virtual void PreUpdate() override;
        virtual void Update() override;

        virtual void UpdateEvent() override;
        void ClearEvent();

        // 이벤트 리스너
        virtual void OnLButtonDown();
        virtual void OnLButtonUp();
        virtual void OnRButtonDown();
        virtual void OnRButtonUp();
        virtual void OnClick();
        virtual void OnRClick();
        virtual void OnDoubleClick();
        virtual void OnEnabledChanged();
        virtual void OnTextChanged();

        virtual Vector2 GetSize();
        Vector2 GetLocation();

        void SetSize(int w, int h);
        void SetSizeByTexture();
        // 좌상단 기준

        virtual void SetLocation(int x, int y);
        virtual void SetLocation(float x, float y);
        virtual void SetLocation(Vector2 pos);
        virtual void SetTexture(const wstring& _key);

		virtual void SetText(const wstring& _text);
		virtual void SetText(int _value);
		virtual void SetText(LPCTSTR pszStr, ...);

        // child
        UI* CreateChild(const std::wstring& _tag, const Vector2& _pos);

        bool Intersect(Vector2 _target);
        RECT GetRect();
        Texture* GetTexture();

        void BringToTop();

        static void HideAllUI();

    public:

        Rectangle* mesh = nullptr;
        Texture* texture = nullptr;
        Vector2 uvRatioStart = { 0, 0 };
        Vector2 uvRatioEnd   = { 1, 1 };
        _D3DCOLORVALUE timerColor{ 31, 91, 142, 200 }; // RGBA
        bool grayscale = false;
        // 넓이 높이 (R)
        Vector2 size;

        wstring text;
    public:
        // 이벤트 (RW)

        Event<MouseEventArg> DoubleClick;
        Event<MouseEventArg> LButtonDown;
        Event<MouseEventArg> LButtonUp;
        Event<MouseEventArg> RButtonDown;
        Event<MouseEventArg> RButtonUp;
        
        Event<MouseEventArg> TextChanged;
        Event<MouseEventArg> EnabledChanged;
        Event<MouseEventArg> Click;
        Event<MouseEventArg> RClick;
    protected:
        // 이벤트 관련 
        bool isLButtonDown = false;
        bool isRButtonDown = false;

        bool clickFlag = false;
        float doubleClickTick = 0.f;
        float doubleClickDelay = 0.4f;

        bool oldEnable = false;

        wstring oldText;

    public:
        static list<UI*> uiList;
    };



}
