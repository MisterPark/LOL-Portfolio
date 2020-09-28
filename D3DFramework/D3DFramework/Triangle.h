#pragma once
#include "Mesh.h"
class Triangle :
    public Mesh
{
public:
    Triangle();
    virtual ~Triangle();

    // Mesh을(를) 통해 상속됨
    virtual void Render() override;

};

