#include "stdafx.h"
#include "Player.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Plane.h"
#include "Terrain.h"

Player::Player()
{
	
	transform->scale = { 0.5f,0.5f,0.5f, };
	AddComponent<PKH::Terrain>(L"Mesh");
}

Player::~Player()
{
}

void Player::Update()
{
}
