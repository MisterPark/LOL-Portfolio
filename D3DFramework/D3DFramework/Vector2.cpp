#include "stdafx.h"
#include "Vector2.h"

PKH::Vector2::Vector2()
{
	x = 0.f;
	y = 0.f;
}

PKH::Vector2::Vector2(D3DXVECTOR2 rhs) :D3DXVECTOR2(rhs)
{
}

PKH::Vector2::Vector2(POINT p) : D3DXVECTOR2(p.x, p.y)
{
}

PKH::Vector2::Vector2(float x, float y) : D3DXVECTOR2(x, y)
{
}

PKH::Vector2::~Vector2()
{
}
