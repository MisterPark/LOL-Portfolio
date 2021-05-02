#include "stdafx.h"
#include "BushGroup.h"

list<BushGroup*> BushGroup::bushGroupList;

BushGroup::BushGroup()
{
	bushGroupList.push_back(this);
}

BushGroup::~BushGroup()
{
}

void BushGroup::Destroy()
{
	for (auto& bushGroup : bushGroupList)
	{
		delete bushGroup;
	}
}