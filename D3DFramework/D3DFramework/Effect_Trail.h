#pragma once
#include "EffectObject.h"

class TrailMesh;

class Effect_Trail :
    public EffectObject
{
public:
    Effect_Trail();
    virtual ~Effect_Trail();

    virtual void PostUpdate() override;

    void SetTrailPos(const Vector3& start, const Vector3& end);

private:
    TrailMesh* mesh = nullptr;
};

