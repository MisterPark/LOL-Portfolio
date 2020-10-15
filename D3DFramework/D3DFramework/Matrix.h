#pragma once
#include <d3dx9math.h>

namespace PKH
{
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
	
		// 역행렬을 반환합니다.
		// Determinant : 행렬식
		// - 역행렬이 존재하지 않으면	0
		// - 역행렬이 존재하면			0이 아닌 값을 반환
		static Matrix Inverse(const Matrix& pMat, float* pOutDeterminant = nullptr);
		

	public:
		static const Matrix identity;
	
	};
}


