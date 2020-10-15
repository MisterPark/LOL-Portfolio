#include "stdafx.h"

const PKH::Color Color::Red = D3DCOLOR_ARGB(255, 255, 0, 0);
const PKH::Color Color::Green = D3DCOLOR_ARGB(255, 0, 255, 0);
const PKH::Color Color::White = D3DCOLOR_ARGB(255, 255, 255, 255);
const PKH::Color Color::Black = D3DCOLOR_ARGB(255, 0, 0, 0);
const PKH::Color Color::Gray = D3DCOLOR_ARGB(255, 128, 128, 128);
const PKH::Color Color::Blue = D3DCOLOR_ARGB(255, 0, 0, 255);

PKH::Color::Color() 
{
}


PKH::Color::Color(D3DCOLOR d3dcolor)
{
	value = d3dcolor;
}

PKH::Color::Color(FLOAT r, FLOAT g, FLOAT b, FLOAT a) 
{
}
