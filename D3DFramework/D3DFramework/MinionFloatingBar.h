#pragma once
#include "FloatingBar.h"
class MinionFloatingBar :
    public FloatingBar
{
public:
    MinionFloatingBar();
    virtual ~MinionFloatingBar();

    virtual void Render() override;
};

