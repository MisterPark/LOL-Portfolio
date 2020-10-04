#include "stdafx.h"
#include "Vector3.h"

using namespace PKH;

PKH::Vector3::Vector3()
{
}

PKH::Vector3::Vector3(D3DXVECTOR3 r) :D3DXVECTOR3(r)
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

float PKH::Vector3::Magnitude() const
{
	return sqrtf(x * x + y * y + z * z);
}

float PKH::Vector3::Length() const
{
	return sqrtf(x * x + y * y + z * z);
}

float PKH::Vector3::SquareMagnitude() const
{
	return x * x + y * y + z * z;
}

Vector3 PKH::Vector3::Normalized() const
{
	Vector3 norm = *this;
	D3DXVec3Normalize(&norm, &norm);
	return norm;
}

float PKH::Vector3::Angle(const Vector3& from, const Vector3& to)
{
	Vector3 v = to - from;
	return D3DXToDegree(atan2f(v.y, v.x));
}

Vector3 PKH::Vector3::Cross(const Vector3* lhs, const Vector3* rhs)
{
	Vector3 result;
	D3DXVec3Cross(&result, lhs, rhs);
	return result;
}

float PKH::Vector3::Distance(const Vector3& a, const Vector3& b)
{
	Vector3 distance = a - b;
	return distance.Magnitude();
}

float PKH::Vector3::Dot(const Vector3* lhs, const Vector3* rhs)
{
	return D3DXVec3Dot(lhs, rhs);
}

void PKH::Vector3::Normalize(Vector3* outV)
{
	D3DXVec3Normalize(outV, outV);
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
