#pragma once
#include "BehaviorTree.h"
#include "Monster.h"

class MonsterSubTree :
    public SelectorNode
{
public:
    MonsterSubTree(Monster* owner);
    virtual~MonsterSubTree();

    Monster* monster = nullptr;

};

