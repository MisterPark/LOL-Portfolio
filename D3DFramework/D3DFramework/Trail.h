#pragma once
#include "IComponent.h"

namespace Engine
{
	class DynamicMesh;
}

class Effect_Trail;

class Trail :
    public IComponent
{
public:
	explicit Trail(GameObject* owner);
	explicit Trail(const Trail& rhs);
	virtual ~Trail();

	virtual void Update() override;
	virtual IComponent* Clone() override;

	void AttachToDynamicMesh(DynamicMesh* dmesh);
	void SetLength(float _length);
	void SetOffset(float _offset);

	void SetVisible(bool _visible);

private:
	DynamicMesh* dynamicMesh = nullptr;
	Effect_Trail* trail = nullptr;
	float length = 1.f;
	float offset = 0.f;
};

