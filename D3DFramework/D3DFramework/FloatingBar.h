#pragma once
#include "UI.h"
#include "Rectangle.h"

using namespace PKH;

class FloatingBar : public UI
{
public:
    FloatingBar();
    virtual ~FloatingBar();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
	virtual void Render() override;

    void SetTarget(GameObject* target);

protected:
    GameObject* target = nullptr;

    Vector3 offset;
    PKH::Rectangle* mesh = nullptr;

    //bool isHover = false;
};

