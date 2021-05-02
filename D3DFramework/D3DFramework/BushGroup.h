#pragma once
#include "Bush.h"
class BushGroup
{
public:
	BushGroup();
	virtual ~BushGroup();

	static void Destroy();


public:
	list<Bush*> bushList;
	static list<BushGroup*> bushGroupList;
};

