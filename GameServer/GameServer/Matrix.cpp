#include "stdafx.h"
#include "Matrix.h"

const PKH::Matrix Matrix::identity = D3DXMATRIX(1, 0, 0, 0,
										0, 1, 0, 0,
										0, 0, 1, 0,
										0, 0, 0, 1);

PKH::Matrix::Matrix() : D3DXMATRIX()
{
}

PKH::Matrix::Matrix(const D3DXMATRIX& r) : D3DXMATRIX(r)
{
	
}

PKH::Matrix::~Matrix()
{
}

Matrix PKH::Matrix::Inverse(const Matrix& pMat, float* pOutDeterminant)
{
	Matrix inverse;
	D3DXMatrixInverse(&inverse, pOutDeterminant, &pMat);
	return inverse;
}

Matrix PKH::Matrix::LookAtLH(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	Vector3 dir = target - pos;
	Vector3 zAxis = dir.Normalized();
	Vector3 xAxis = Vector3::Cross(up, zAxis).Normalized();
	Vector3 yAxis = Vector3::Cross(zAxis, xAxis).Normalized();

	Matrix mat;
	mat._11 = xAxis.x;
	mat._12 = yAxis.x;
	mat._13 = zAxis.x;
	mat._14 = 0;
	
	mat._21 = xAxis.y;
	mat._22 = yAxis.y;
	mat._23 = zAxis.y;
	mat._24 = 0;

	mat._31 = xAxis.z;
	mat._32 = yAxis.z;
	mat._33 = zAxis.z;
	mat._34 = 0;

	mat._41 = -Vector3::Dot(xAxis, pos);
	mat._42 = -Vector3::Dot(yAxis, pos);
	mat._43 = -Vector3::Dot(zAxis, pos);
	mat._44 = 1;

	return mat;
}

Matrix PKH::Matrix::PerspectiveFovLH(float fovY, float aspect, float zn, float zf)
{
	float yScale = 1.f / tanf(fovY * 0.5f);
	float xScale = yScale / aspect;


	Matrix mat = Matrix::identity;
	mat._11 = xScale;
	mat._22 = yScale;
	mat._33 = zf / (zf - zn);
	mat._34 = 1;
	mat._43 = -zn * zf / (zf - zn);
	mat._44 = 0;
	return mat;
}
