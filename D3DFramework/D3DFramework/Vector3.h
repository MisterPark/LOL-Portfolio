#pragma once
#include <d3dx9.h>

namespace PKH
{
	class Vector3 : public D3DXVECTOR3
	{
	public:
		Vector3();
		Vector3(D3DXVECTOR3 r);
		Vector3(POINT r);
		Vector3(float x, float y, float z);
		~Vector3();

		//=====================================
		// operator
		//=====================================

		using D3DXVECTOR3::operator const FLOAT*;
		using D3DXVECTOR3::operator FLOAT*;
		using D3DXVECTOR3::operator*;
		using D3DXVECTOR3::operator*=;
		using D3DXVECTOR3::operator+;
		using D3DXVECTOR3::operator+=;
		using D3DXVECTOR3::operator-;
		using D3DXVECTOR3::operator-=;
		using D3DXVECTOR3::operator/;
		using D3DXVECTOR3::operator/=;
		using D3DXVECTOR3::operator==;
		using D3DXVECTOR3::operator!=;
		
		//=====================================
		// Public Function
		//=====================================
		
		// 벡터의 길이를 반환합니다.
		float Magnitude() const;
		// 벡터의 길이를 반환합니다.
		float Length() const;
		// 벡터의 길이의 제곱을 반환합니다.
		float SquareMagnitude() const;
		// 해당 벡터의 단위벡터를 반환합니다.
		// 주의 : 
		// 해당 벡터의 값은 바뀌지 않습니다.
		// 해당 벡터의 값을 바꾸려면
		// Vector3::Normalize() 를 사용하세요.
		Vector3 Normalized() const;

		//=====================================
		// Static Function
		//=====================================

		// from 부터 to 사이의 각을 구합니다.
		// 단위 Degree
		// 범위 -180 ~ 180
		static float	Angle(const Vector3& from, const Vector3& to);
		// 두 벡터의 외적
		static Vector3	Cross(const Vector3* lhs, const Vector3* rhs);
		// a와 b사이의 거리를 반환합니다.
		static float	Distance(const Vector3& a, const Vector3& b);
		// 두 벡터의 내적
		static float	Dot(const Vector3* lhs, const Vector3* rhs);
		// 벡터를 Normalize 합니다.
		static void		Normalize(Vector3* outV);


		//=====================================
		// static variables
		//=====================================

		// (-1,0,0)
		static const Vector3 left;
		// (1,0,0)
		static const Vector3 right;
		// (0,1,0)
		static const Vector3 up;
		// (0,-1,0)
		static const Vector3 down;
		// (0,0,1)
		static const Vector3 forward;
		// (0,0,-1)
		static const Vector3 back;
		// (1,1,1)
		static const Vector3 one;
		// (0,0,0)
		static const Vector3 zero;
	};
	const Vector3 Vector3::left		= Vector3(-1.f, 0.f, 0.f);
	const Vector3 Vector3::right	= Vector3(1.f, 0.f, 0.f);
	const Vector3 Vector3::up		= Vector3(0.f, 1.f, 0.f);
	const Vector3 Vector3::down		= Vector3(0.f, -1.f, 0.f);
	const Vector3 Vector3::forward	= Vector3(0.f, 0.f, 1.f);
	const Vector3 Vector3::back		= Vector3(0.f, 0.f, -1.f);
	const Vector3 Vector3::one		= Vector3(1.f, 1.f, 1.f);
	const Vector3 Vector3::zero		= Vector3(0.f, 0.f, 0.f);

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


