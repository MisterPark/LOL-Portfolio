#include "stdafx.h"
#include "Animation2D.h"

PKH::Animation2D::Animation2D()
{
}

PKH::Animation2D::~Animation2D()
{
}

void PKH::Animation2D::Update()
{
	if (nullptr == gameObject)
	{
		return;
	}
		

	tick += TimeManager::DeltaTime();
	if (tick > delay)
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
		
		currentTexture = (TextureKey)i;
		
	}
	Mesh* mesh = (Mesh*)gameObject->GetComponent(L"Mesh");
	mesh->SetTexture(currentTexture);

}

void PKH::Animation2D::SetSprite(TextureKey _startTexture, TextureKey _endTexture)
{
	startTexture = _startTexture;
	endTexture = _endTexture;
	if ((int)currentTexture < (int)startTexture
		|| (int)currentTexture >(int)endTexture)
	{
		currentTexture = startTexture;
	}
	
}

void PKH::Animation2D::SetCurrentSprite(TextureKey _currentTexture)
{
	currentTexture = _currentTexture;
}

void PKH::Animation2D::SetLoop(bool _isLoop)
{
	isLoop = _isLoop;
}

void PKH::Animation2D::SetDelay(float _delay)
{
	delay = _delay;
}

void PKH::Animation2D::SetTick(float _tick)
{
	tick = _tick;
}

TextureKey PKH::Animation2D::GetCurrentSprite()
{
	return currentTexture;
}

TextureKey PKH::Animation2D::GetStartSprite()
{
	return startTexture;
}

TextureKey PKH::Animation2D::GetEndSprite()
{
	return endTexture;
}

bool PKH::Animation2D::IsEndFrame()
{
	return isEndFrame;
}

IComponent* PKH::Animation2D::Clone()
{
    return nullptr;
}
