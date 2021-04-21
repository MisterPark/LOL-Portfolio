#include "stdafx.h"
#include "Animation2D.h"


Engine::Animation2D::Animation2D(GameObject* owner)
	:IComponent(owner)
{

}

Engine::Animation2D::Animation2D(const Animation2D& rhs)
	:IComponent(rhs)
{
}

Engine::Animation2D::~Animation2D()
{
}

void Engine::Animation2D::Update()
{
	if (nullptr == gameObject)
	{
		return;
	}
		

	tick += Time::DeltaTime();
	if (isPlay && (tick > delay))
	{
		tick = 0;

		if (currentTexture == endTexture)
		{
			isEndFrame = true;

			if (isLoop == true)
			{
				currentTexture = startTexture;
			}
			return;
		}
		else
		{
			isEndFrame = false;
		}
		int i = int(currentTexture);
		i++;
		
		currentTexture = (TextureID)i;
		
	}

	wstring key = RenderManager::GetTextureKey(currentTexture);
	if (mesh != nullptr) {
		mesh->SetTexture(key.c_str());
	}

}

void Engine::Animation2D::SetMesh(CustomMesh* _mesh)
{
	mesh = _mesh;
}

void Engine::Animation2D::SetSprite(TextureID _startTexture, TextureID _endTexture)
{
	startTexture = _startTexture;
	endTexture = _endTexture;
	if ((int)currentTexture < (int)startTexture
		|| (int)currentTexture >(int)endTexture)
	{
		currentTexture = startTexture;
	}
	
}

void Engine::Animation2D::SetCurrentSprite(TextureID _currentTexture)
{
	currentTexture = _currentTexture;
}

void Engine::Animation2D::SetLoop(bool _isLoop)
{
	isLoop = _isLoop;
}

void Engine::Animation2D::SetDelay(float _delay)
{
	delay = _delay;
}

void Engine::Animation2D::SetTick(float _tick)
{
	tick = _tick;
}

void Engine::Animation2D::SetPlay(bool _play)
{
	isPlay = _play;
}

void Engine::Animation2D::Initialize()
{
	currentTexture = startTexture;
	tick = 0;
	isEndFrame = false;
}

TextureID Engine::Animation2D::GetCurrentSprite()
{
	return currentTexture;
}

TextureID Engine::Animation2D::GetStartSprite()
{
	return startTexture;
}

TextureID Engine::Animation2D::GetEndSprite()
{
	return endTexture;
}

bool Engine::Animation2D::IsEndFrame()
{
	return isEndFrame;
}

IComponent* Engine::Animation2D::Clone()
{
    return nullptr;
}
