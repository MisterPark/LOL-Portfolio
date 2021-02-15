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

PKH::Vector2::Vector2(POINT p) : D3DXVECTOR2((FLOAT)p.x, (FLOAT)p.y)
{
}

PKH::Vector2::Vector2(int x, int y) : D3DXVECTOR2((FLOAT)x, (FLOAT)y)
{
}

PKH::Vector2::Vector2(float x, float y) : D3DXVECTOR2(x, y)
{
}

PKH::Vector2::~Vector2()
{
}
