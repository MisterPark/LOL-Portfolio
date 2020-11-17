#include "stdafx.h"
#include "Mesh.h"

PKH::Mesh::Mesh()
	:isClone(false)
{
}

PKH::Mesh::Mesh(const Mesh& rhs)
	:isClone(true)
{
}

PKH::Mesh::~Mesh()
{
}
