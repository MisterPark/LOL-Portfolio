#pragma once
#include "GameObject.h"

class Pointing : public GameObject
{
public:
    Pointing();
    virtual ~Pointing();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void Show() override;
};

