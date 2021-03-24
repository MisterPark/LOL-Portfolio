#pragma once
#include "BehaviorTree.h"
#include "Minion.h"

class MinionSubTree :
    public SelectorNode
{
public:
    MinionSubTree(Minion* owner);
    virtual ~MinionSubTree();

    Minion* minion = nullptr;
};

