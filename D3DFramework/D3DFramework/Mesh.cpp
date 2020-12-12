#include "stdafx.h"
#include "Mesh.h"

PKH::Mesh::Mesh(GameObject* owner)
	:IComponent(owner)
	,isClone(false)
{
	type = MeshType::NONE;
}

PKH::Mesh::Mesh(const Mesh& rhs)
	:IComponent(rhs)
	,isClone(true)
	,type(rhs.type)
{
}

PKH::Mesh::~Mesh()
{
}
