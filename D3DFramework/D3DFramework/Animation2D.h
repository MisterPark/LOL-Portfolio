#pragma once
#include "IComponent.h"
namespace Engine{

class Animation2D :
    public IComponent
{
public:
    explicit Animation2D(GameObject* owner);
    explicit Animation2D(const Animation2D& rhs);
    virtual ~Animation2D();
    virtual void Update();

    void SetSprite(TextureID _startTexture, TextureID _endTexture);
	void SetCurrentSprite(TextureID _currentTexture);
	void SetLoop(bool _isLoop);
    void SetDelay(float _delay);
	void SetTick(float _tick);
    TextureID GetCurrentSprite();
    TextureID GetStartSprite();
    TextureID GetEndSprite();
	bool IsEndFrame();
    // IComponent을(를) 통해 상속됨
    virtual IComponent* Clone() override;
    
private:

    TextureID startTexture;
    TextureID currentTexture;
    TextureID endTexture;

    float delay = 0.2f;
    float tick = 0.f;
    bool isLoop = false;
	bool isEndFrame = false;
};
}
