#pragma once
#include "GameObject.h"
#include "Rectangle.h"

namespace PKH
{
    class UI : public GameObject
    {
    public:
        UI();
        virtual ~UI();

        virtual void Update() override;
        virtual void Render() override;

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
        virtual void OnChangedText();

        Vector3 GetSize();
        Vector3 GetLocation();

        void SetSize(int w, int h);
        void SetSizeByTexture();
        // 좌상단 기준

        void SetLocation(int x, int y);
        void SetTexture(const wstring& _key);


    public:
        
        //wstring textureKey;
        Rectangle* mesh = nullptr;
        Texture* texture = nullptr;

        // 텍스트 관련
        wstring text; // 출력할 텍스트 (RW)
        D3DCOLOR foreColor;
        Vector3 textOffsetPosition;// 텍스트를 출력할 local(offset)위치 (RW) 
        bool textRenderFlag = false;// 텍스트를 출력할 UI인가? (RW)

        // 넓이 높이 (R)
        int width = 0;
        int height = 0;

    public:
        // 이벤트 콜백 (RW)
        void (*Click)() = nullptr;
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

        wstring oldText;

    };



}
