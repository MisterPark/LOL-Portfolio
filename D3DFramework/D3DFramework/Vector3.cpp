#include "stdafx.h"
#include "Vector3.h"

using namespace PKH;

const Vector3 Vector3::LEFT = Vector3(-1.f, 0.f, 0.f);
const Vector3 Vector3::RIGHT = Vector3(1.f, 0.f, 0.f);
const Vector3 Vector3::UP = Vector3(0.f, 1.f, 0.f);
const Vector3 Vector3::DOWN = Vector3(0.f, -1.f, 0.f);
const Vector3 Vector3::FORWARD = Vector3(0.f, 0.f, 1.f);
const Vector3 Vector3::BACK = Vector3(0.f, 0.f, -1.f);
const Vector3 Vector3::ONE = Vector3(1.f, 1.f, 1.f);
const Vector3 Vector3::ZERO = Vector3(0.f, 0.f, 0.f);

PKH::Vector3::Vector3()
{
}

PKH::Vector3::Vector3(D3DXVECTOR3 r) :D3DXVECTOR3(r)
{
}

PKH::Vector3::Vector3(POINT r) :D3DXVECTOR3((FLOAT)r.x, (FLOAT)r.y, 0.f)
{
}

PKH::Vector3::Vector3(float x, float y, float z) : D3DXVECTOR3(x,y,z)
{
}

PKH::Vector3::~Vector3()
{
}

bool PKH::Vector3::operator==(const Vector3& other)
{
	if (this->x != other.x) return false;
	if (this->y != other.y) return false;
	if (this->z != other.z) return false;
	return true;
}

bool PKH::Vector3::operator!=(const Vector3& other)
{
	if (this->x != other.x) return true;
	if (this->y != other.y) return true;
	if (this->z != other.z) return true;
	return false;
}

Vector3& PKH::Vector3::operator=(const Vector3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;

	return *this;
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

	float len = norm.Length();
	norm.x /= len;
	norm.y /= len;
	norm.z /= len;

	return norm;
}

float PKH::Vector3::AngleX(const Vector3 & from, const Vector3 & to)
{
	Vector3 v = to - from;
	return D3DXToDegree(atan2f(v.z, v.y));
}

float PKH::Vector3::AngleY(const Vector3 & from, const Vector3 & to)
{
	Vector3 v = to - from;
	return atan2f(v.x, v.z);

	//Vector3 a = from.Normalized();
	//Vector3 b = to.Normalized();
	//a.y = 0;
	//b.y = 0;
	//float angle = acosf(Vector3::Dot(a, b));

	//return angle;
}

float PKH::Vector3::AngleZ(const Vector3& from, const Vector3& to)
{
	Vector3 v = to - from;
	return D3DXToDegree(atan2f(v.y, v.x));
}

Vector3 PKH::Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 result;
	//D3DXVec3Cross(&result, &lhs, &rhs);
	// i  j  k
	// ux uy uz
	// vx vy vz

	result.x = lhs.y * rhs.z - lhs.z * rhs.y;
	result.y = lhs.z * rhs.x - lhs.x * rhs.z;
	result.z = lhs.x * rhs.y - lhs.y * rhs.x;

	return result;
}

float PKH::Vector3::Distance(const Vector3& a, const Vector3& b)
{
	Vector3 distance = a - b;
	float dist = distance.Magnitude();
	return dist;
}

float PKH::Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
{
	//return D3DXVec3Dot(&lhs, &rhs);
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

void PKH::Vector3::Normalize(Vector3* outV)
{
	//D3DXVec3Normalize(outV, outV);
	*outV = outV->Normalized();
}
