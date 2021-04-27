#pragma once
#include "CustomMesh.h"
class TrailMesh :
    public CustomMesh
{
public:
    explicit TrailMesh(GameObject* owner);
    explicit TrailMesh(const TrailMesh& rhs);
    virtual ~TrailMesh();

    virtual void Update() override;
    virtual IComponent* Clone() override;
    virtual void CreateCustomMesh() override;

    void SetTrailPos(const Vector3& start, const Vector3 end);
private:
    Vector3 start;
    Vector3 end;
    float tick = 0.f;
    float delay = 0.1f;

    queue<pair<Vector3, Vector3>> posQ;
};

