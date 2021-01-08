#pragma once
#include "UI.h"
class LoadingChampPanel :
    public UI
{
public:
    LoadingChampPanel();
    virtual ~LoadingChampPanel();

    virtual void Initialize() override;
    virtual void Release() override;
};

