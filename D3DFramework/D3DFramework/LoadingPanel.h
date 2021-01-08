#pragma once
#include "UI.h"
class LoadingPanel :
    public UI
{
public:
    LoadingPanel();
    virtual ~LoadingPanel();

    virtual void Initialize() override;
    virtual void Release() override;
};

