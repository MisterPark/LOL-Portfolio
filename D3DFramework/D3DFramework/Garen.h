#pragma once
#include "Champion.h"
class Garen :
    public Champion
{
public:
    Garen();
    virtual ~Garen();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;


};

