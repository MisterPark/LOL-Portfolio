#include "stdafx.h"
#include "Vector3.h"

using namespace PKH;

PKH::Vector3::Vector3()
{
}

PKH::Vector3::Vector3(const D3DXVECTOR3& r) :D3DXVECTOR3(r)
{
}

PKH::Vector3::Vector3(POINT r) :D3DXVECTOR3(r.x, r.y, 0.f)
{
}

PKH::Vector3::Vector3(float x, float y, float z) : D3DXVECTOR3(x,y,z)
{
}

PKH::Vector3::~Vector3()
{
}

PKH::Matrix::Matrix() : D3DXMATRIX()
{
}

PKH::Matrix::Matrix(const D3DXMATRIX& r) : D3DXMATRIX(r)
{
}

PKH::Matrix::~Matrix()
{
}
