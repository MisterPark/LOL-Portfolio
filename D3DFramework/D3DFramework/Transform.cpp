#include "stdafx.h"
#include "transform.h"

using namespace PKH;

PKH::Transform::Transform()
{
}

PKH::Transform::~Transform()
{
}

void PKH::Transform::Update()
{
    //Vector3 rotX, rotY, rotX;
    //target.x = cosf(rotation.z + D3DXToRadian(90.f));
    //target.y = sinf(rotation.z + D3DXToRadian(90.f));
}

IComponent* PKH::Transform::Clone()
{
    return nullptr;
}
