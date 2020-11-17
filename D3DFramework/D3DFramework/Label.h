#pragma once
#include "UI.h"
class Label :
    public UI
{
public:
    Label();
    virtual ~Label();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void UpdateUI() override;
    virtual void Update() override;
    virtual void Render() override;

};

