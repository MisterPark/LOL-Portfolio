#include "stdafx.h"
#include "Mesh.h"

PKH::Mesh::Mesh(GameObject* owner)
	:IComponent(owner)
	,isClone(false)
{
}

PKH::Mesh::Mesh(const Mesh& rhs)
	:IComponent(rhs)
	,isClone(true)
{
}

PKH::Mesh::~Mesh()
{
}
