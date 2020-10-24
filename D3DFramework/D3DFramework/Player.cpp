#include "stdafx.h"
#include "Player.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Plane.h"
#include "Terrain.h"

Player::Player()
{
	
	//transform->scale = { 0.5f,0.5f,0.5f, };
	Terrain* t = (Terrain*)AddComponent<PKH::Terrain>(L"Mesh");
	t->LoadHeightMap("Texture\\Height2.bmp");
}

Player::~Player()
{
}

void Player::Update()
{
	GameObject::Update();
}
