#pragma once
#include "FloatingBar.h"
class TurretFloatingBar :
    public FloatingBar
{
public:
    TurretFloatingBar();
    virtual ~TurretFloatingBar();

    virtual void Render() override;


};

