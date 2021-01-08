#pragma once
#include "GameObject.h"
#include "Rectangle.h"


class FloatingBar :
    public GameObject
{
public:
    FloatingBar();
    virtual ~FloatingBar();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    void SetTarget(GameObject* target);

protected:
    GameObject* target = nullptr;
    Vector3 offset;
    PKH::Rectangle* mesh = nullptr;

    bool isHover = false;
};

