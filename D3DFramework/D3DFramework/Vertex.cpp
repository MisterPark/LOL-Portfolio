#include "stdafx.h"
#include "Vertex.h"

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
const DWORD VertexUV::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

PKH::Vertex::Vertex(float _x, float _y, float _z, D3DCOLOR _color)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->color = _color;

}

PKH::VertexUV::VertexUV(float _x, float _y, float _z, float _u, float _v)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->u = _u;
	this->v = _v;
}
