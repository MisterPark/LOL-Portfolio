#include "stdafx.h"
#include "UnitStat.h"

UnitStat::UnitStat(GameObject* owner) :IComponent(owner)
{
}

UnitStat::UnitStat(const UnitStat& rhs) : IComponent(rhs)
{
}

UnitStat::~UnitStat()
{
}

IComponent* UnitStat::Clone()
{
    return new UnitStat(*this);
}
