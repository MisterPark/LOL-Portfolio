#include "stdafx.h"
#include "Water.h"


Water::Water()
{
	Initialize();
}

Water::~Water()
{

}

void Water::Initialize()
{
	terrain = (Terrain*)AddComponent<PKH::Terrain>(L"Mesh");
	terrain->SetBlendMode(BlendMode::ALPHA_TEST);
	anim = (Animation2D*)AddComponent<Animation2D>(L"Animation2D");


	anim->SetSprite(TextureKey::WATER_WATER_ENVIRONMENT01, TextureKey::WATER_WATER_ENVIRONMENT03);
	anim->SetDelay(1.f);
	anim->SetLoop(true);

	
		
	
}

void Water::Release()
{
}

void Water::Update()
{

	GameObject::Update();
	
	
}


void Water::WaterTextureChange(TextureKey _StartKey, TextureKey _EndKey, bool _isLoop, float _delay)
{
	anim->SetSprite(_StartKey, _EndKey);
	anim->SetLoop(_isLoop);
	if(_isLoop==true)
	anim->SetDelay(_delay);
}

void Water::Lava()
{
	anim->SetSprite(TextureKey::FIRE_WATER_ENVIRONMENT02, TextureKey::FIRE_WATER_ENVIRONMENT02);
	anim->SetLoop(false);
}

void Water::Beach()
{
	anim->SetSprite(TextureKey::WATER_WATER_ENVIRONMENT, TextureKey::WATER_WATER_ENVIRONMENT);
	anim->SetLoop(false);
}

void Water::Normal()
{
	anim->SetSprite(TextureKey::GRASS_WATER_ENVIRONMENT, TextureKey::GRASS_WATER_ENVIRONMENT);
	anim->SetLoop(false);
}
