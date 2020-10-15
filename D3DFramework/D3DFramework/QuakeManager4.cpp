#include "stdafx.h"
#include "QuakeManager4.h"
#include "CollisionManager4.h"

using namespace PKH;

PKH::QuakeManager4* PKH::QuakeManager4::pInstance = nullptr;

PKH::QuakeManager4::QuakeManager4()
{
    QuakePos = 0.f;
    QuakeStart = 0;
}

PKH::QuakeManager4::~QuakeManager4()
{
}

QuakeManager4* PKH::QuakeManager4::GetInstance()
{
    if (nullptr == pInstance)
    {
        pInstance = new QuakeManager4;
    }
    return pInstance;
}

void PKH::QuakeManager4::Destroy()
{
    delete pInstance;
    pInstance = nullptr;
}

void PKH::QuakeManager4::Update()
{
    switch (pInstance->QuakeStart){
    case 1:
        pInstance->QuakePos = 0.1f;
        pInstance->QuakeStart = 2;
        ObjPosSetQuake();
        break;
    case 2:
        pInstance->QuakePos = -0.2f;
        pInstance->QuakeStart = 3;
        ObjPosSetQuake();
        break;
    case 3:
        pInstance->QuakePos = +0.3f;
        pInstance->QuakeStart = 4;
        ObjPosSetQuake();
        break;
    case 4:
        pInstance->QuakePos = -0.4f;
        pInstance->QuakeStart = 5;
        ObjPosSetQuake();
        break;
    case 5:
        pInstance->QuakePos = 0.2f;
        pInstance->QuakeStart = 0;
        ObjPosSetQuake();
        break;
    default:
        break;
    }

}

void PKH::QuakeManager4::ObjPosSetQuake() {
    for (int i = 0; i < PKH::CollisionManager4::OBJTAG::TAG_END; i++)
    {
        for (auto& obj : *PKH::CollisionManager4::GetInstance()->GetObjList2(i)) {
            obj->transform->position.y += pInstance->QuakePos;
        }
    }
}
