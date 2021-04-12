#pragma once
#include "IComponent.h"

class Effect_Red_Buff;
class Effect_Blue_Buff;
class Effect_Baron_Buff;

class Aura :
    public IComponent
{
public:
	explicit Aura(GameObject* owner);
	explicit Aura(const Aura& rhs);
	virtual ~Aura();

	virtual void PostUpdate() override;

    virtual IComponent* Clone() override;

	void ShowRedBuff(bool _show);
	void ShowBlueBuff(bool _show);
	void ShowBaronBuff(bool _show);

private:
	float angle = 0.f;

	Effect_Red_Buff* redBuff = nullptr;
	Effect_Blue_Buff* blueBuff = nullptr;
	Effect_Baron_Buff* baronBuff = nullptr;
};

