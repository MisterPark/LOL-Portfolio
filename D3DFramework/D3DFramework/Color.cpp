#include "stdafx.h"

const Engine::Color Color::RedMonster = D3DCOLOR_ARGB(255, 255, 0, 0);
const Engine::Color Color::Green = D3DCOLOR_ARGB(255, 0, 255, 0);
const Engine::Color Color::White = D3DCOLOR_ARGB(255, 255, 255, 255);
const Engine::Color Color::Black = D3DCOLOR_ARGB(255, 0, 0, 0);
const Engine::Color Color::Gray = D3DCOLOR_ARGB(255, 128, 128, 128);
const Engine::Color Color::BlueMonster = D3DCOLOR_ARGB(255, 0, 0, 255);

Engine::Color::Color() 
{

}


Engine::Color::Color(D3DCOLOR d3dcolor)
{
	value = d3dcolor;
}

Engine::Color::Color(FLOAT r, FLOAT g, FLOAT b, FLOAT a) 
{
}
