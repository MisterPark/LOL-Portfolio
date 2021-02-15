#include "stdafx.h"
#include "LoadingBackGround.h"
LoadingBackGround::LoadingBackGround()
{
	SetTexture(L"srbackground");
	//SetLocation(100, 100);
	//transform->position = { 100,0,0 };
	//transform->scale = { 50,50,1 };
	
	SetSize(MainGame::GetWidth(), MainGame::GetHeight());
	SetLocation(0, 0);

}

LoadingBackGround::~LoadingBackGround()
{


}

void LoadingBackGround::Initialize()
{
}

void LoadingBackGround::Release()
{
}

void LoadingBackGround::Update()
{
	UI::Update();
}
