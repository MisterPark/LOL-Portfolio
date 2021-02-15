#pragma once
#include "GameObject.h"
#include "Unit.h"

using namespace PKH;

class Indicator :
    public GameObject
{
public:
    Indicator();
    virtual ~Indicator();


    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;


    void SetTarget(Unit* _target);

protected:
    Unit* target = nullptr;
};

