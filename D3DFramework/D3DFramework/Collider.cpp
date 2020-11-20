#include "stdafx.h"
#include "Collider.h"

IComponent* Collider::Clone()
{
    return new Collider(*this);
}
