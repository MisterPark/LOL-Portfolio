#include "stdafx.h"
#include "Light.h"

UINT uniqueLightIndex = 0;

Light::Light()
{
	Initialize();
}

Light::~Light()
{
	Release();
}

void Light::Initialize()
{
	ZeroMemory(&lightInfo, sizeof(D3DLIGHT9));

	// 라이트 세팅
	// TODO : 경훈 /일단은 디렉셔널라이트 . 추후에 상속으로 나눌것
	lightInfo.Type = D3DLIGHT_DIRECTIONAL;

	lightInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	lightInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	lightInfo.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	lightInfo.Direction = Vector3(0.f, -1.f, 1.f);
	// 인덱스 세팅
	index = uniqueLightIndex;
	uniqueLightIndex++;

	RenderManager::LockDevice();
	RenderManager::GetDevice()->SetLight(index, &lightInfo);
	RenderManager::GetDevice()->LightEnable(index, TRUE);
	RenderManager::UnlockDevice();

	LightManager::RegisterObject(this);
}

void Light::Release()
{
	RenderManager::LockDevice();
	RenderManager::GetDevice()->LightEnable(index, FALSE);
	RenderManager::UnlockDevice();
	LightManager::DisregisterObject(this);
}

void Light::Update()
{
}

