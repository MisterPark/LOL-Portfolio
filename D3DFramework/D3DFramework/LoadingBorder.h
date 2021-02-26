#pragma once
#include "UI.h"
#include "Rectangle.h"

using namespace Engine;

class LoadingBorder :
    public UI
{
public:
    LoadingBorder();
    virtual ~LoadingBorder();

    virtual void Initialize() override;
    virtual void Release() override;

};

