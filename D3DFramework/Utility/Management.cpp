#include "stdafx.h"
#include "Management.h"

Management* pManagement = nullptr;

Management::Management()
{
}

Management::~Management()
{
}

Management * Management::GetInstance()
{
	if (pManagement == nullptr)
	{
		pManagement = new Management;
	}
	return pManagement;
}

void Management::Destroy()
{
	if (pManagement)
	{
		delete pManagement;
		pManagement = nullptr;
	}
}
