#include "stdafx.h"
#include "Mesh.h"

using namespace PKH;

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

PKH::IComponent * PKH::Mesh::Clone()
{
	return new Mesh(*this);
}
