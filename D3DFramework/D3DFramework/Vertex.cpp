#include "stdafx.h"
#include "Vertex.h"

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;
const DWORD VertexColor::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
const DWORD VertexUV::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

Engine::Vertex::Vertex(Vector3 _pos, D3DCOLOR _color, float _u, float _v)
{
	this->pos = _pos;
	this->color = _color;
	this->normal = Vector3::UP;
	this->u = _u;
	this->v = _v;
}


Engine::VertexColor::VertexColor(float _x, float _y, float _z, D3DCOLOR _color)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->color = _color;

}

Engine::VertexUV::VertexUV(float _x, float _y, float _z, float _u, float _v)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->u = _u;
	this->v = _v;
}

