#pragma once
#include "GameObject.h"


// 맵툴 버려서 만든 애 (실제 플레이에선 쓰이지 않음)
class NavNode :
    public GameObject
{
public:
    NavNode();
    virtual ~NavNode();
    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void OnCollisionEnter(Collider* target) override;


public:
    int uniqueID = -1;
    vector<int> adjacencyArr;
    SphereCollider* collider = nullptr;
};

