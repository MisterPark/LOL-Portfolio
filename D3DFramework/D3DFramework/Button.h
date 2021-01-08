#pragma once
#include "UI.h"
class Button :
    public UI
{
public:
    Button();
    virtual ~Button();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void OnHover() override;
    virtual void OnLeave() override;
    virtual void OnLButtonDown() override;
    virtual void OnLButtonUp() override;
    virtual void OnClick() override;


private:
    // hover 이벤트 전용
    float upScaleRatio = 1.1f;
    Vector3 originScale;
    bool isUpScale = false;
    // down 이벤트 전용
    Vector3 originPosition;
    bool isButtonDown = false;
    
};

