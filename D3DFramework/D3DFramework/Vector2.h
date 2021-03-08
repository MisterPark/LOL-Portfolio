#pragma once
#include <d3dx9math.h>

namespace Engine
{
	class Vector2 : public D3DXVECTOR2
	{
	public:
		Vector2();
		Vector2(D3DXVECTOR2 rhs);
		Vector2(POINT p);
		Vector2(int x, int y);
		Vector2(float x, float y);
		Vector2(D3DXVECTOR3 r);
		~Vector2();

		using D3DXVECTOR2::operator const FLOAT*;
		using D3DXVECTOR2::operator FLOAT*;
		using D3DXVECTOR2::operator*;
		using D3DXVECTOR2::operator*=;
		using D3DXVECTOR2::operator+;
		using D3DXVECTOR2::operator+=;
		using D3DXVECTOR2::operator-;
		using D3DXVECTOR2::operator-=;
		using D3DXVECTOR2::operator/;
		using D3DXVECTOR2::operator/=;
		using D3DXVECTOR2::operator==;
		using D3DXVECTOR2::operator!=;
	};
}


