#pragma once
#include "BehaviorTree.h"
#include "Turret.h"

class TurretSubTree :
    public SelectorNode
{
public:
    TurretSubTree(Turret* owner);
    virtual~TurretSubTree();

    Turret* turret = nullptr;
};

