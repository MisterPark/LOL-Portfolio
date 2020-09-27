#pragma once
#include <d3dx9.h>

namespace PKH
{
	class Vector3 : public D3DXVECTOR3
	{
	public:
		Vector3();
		Vector3(const D3DXVECTOR3& r);
		Vector3(POINT r);
		Vector3(float x, float y, float z);
		~Vector3();

		using D3DXVECTOR3::operator+;
		using D3DXVECTOR3::operator+=;

	};

	class Matrix : public D3DXMATRIX
	{
	public:
		Matrix();
		Matrix(const D3DXMATRIX& r);
		~Matrix();

		using D3DXMATRIX::operator const FLOAT*;
		using D3DXMATRIX::operator FLOAT*;
		using D3DXMATRIX::operator*;
		using D3DXMATRIX::operator();
		using D3DXMATRIX::operator*=;
		using D3DXMATRIX::operator+;
		using D3DXMATRIX::operator+=;
		using D3DXMATRIX::operator-;
		using D3DXMATRIX::operator-=;
		using D3DXMATRIX::operator/;
		using D3DXMATRIX::operator/=;
		using D3DXMATRIX::operator==;
		using D3DXMATRIX::operator!=;
	};
}


