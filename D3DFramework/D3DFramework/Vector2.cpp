#include "stdafx.h"
#include "Vector2.h"

Engine::Vector2::Vector2()
{
	x = 0.f;
	y = 0.f;
}

Engine::Vector2::Vector2(D3DXVECTOR2 rhs) :D3DXVECTOR2(rhs)
{
}

Engine::Vector2::Vector2(POINT p) : D3DXVECTOR2((FLOAT)p.x, (FLOAT)p.y)
{
}

Engine::Vector2::Vector2(int x, int y) : D3DXVECTOR2((FLOAT)x, (FLOAT)y)
{
}

Engine::Vector2::Vector2(float x, float y) : D3DXVECTOR2(x, y)
{
}

Engine::Vector2::Vector2(D3DXVECTOR3 r)
{
	this->x = r.x;
	this->y = r.y;
}

Engine::Vector2::~Vector2()
{
}
