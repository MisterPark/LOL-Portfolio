#pragma once
#include "BehaviorTree.h"
#include "Champion.h"

class ChampionSubTree : public SelectorNode
{
public:
	ChampionSubTree(Champion* owner);
	virtual ~ChampionSubTree();

	Champion* champ = nullptr;
};

