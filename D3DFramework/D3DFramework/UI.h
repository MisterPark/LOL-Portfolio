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


        void UpdateEvent();
        void ClearEvent();

        // �̺�Ʈ ������
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
        // �»�� ����

        void SetLocation(int x, int y);
        void SetLocation(float x, float y);
        void SetLocation(Vector2 pos);
        void SetTexture(const wstring& _key);



    public:
        
        //wstring textureKey;
        Rectangle* mesh = nullptr;
        Texture* texture = nullptr;

        // �ؽ�Ʈ ����
        wstring text; // ����� �ؽ�Ʈ (RW)
        D3DCOLOR foreColor = D3DCOLOR_ARGB(255, 1, 1, 1);
        Vector3 textOffsetPosition;// �ؽ�Ʈ�� ����� local(offset)��ġ (RW) 
        bool textRenderFlag = false;// �ؽ�Ʈ�� ����� UI�ΰ�? (RW)

        // ���� ���� (R)
        int width = 0;
        int height = 0;

    public:
        // �̺�Ʈ �ݹ� (RW)
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
        // �̺�Ʈ ���� 
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
