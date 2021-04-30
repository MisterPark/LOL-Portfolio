#include "stdafx.h"
#include "ArrowPointer.h"
#include "Pointing.h"

ArrowPointer* self = nullptr;

ArrowPointer::ArrowPointer()
{
    Pointing* pointing = CreateChild<Pointing>(L"1");
    Pointing* pointing2 = CreateChild<Pointing>(L"2");
    Pointing* pointing3 = CreateChild<Pointing>(L"3");
    Pointing* pointing4 = CreateChild<Pointing>(L"4");
    pointing2->transform->eulerAngles.y = D3DXToRadian(90.f);
    pointing3->transform->eulerAngles.y = D3DXToRadian(45.f);
    pointing4->transform->eulerAngles.y = D3DXToRadian(135.f);
}

ArrowPointer::~ArrowPointer()
{
}

ArrowPointer* ArrowPointer::GetInstance()
{
    if (self == nullptr)
    {
        self = new ArrowPointer();
    }
    return self;
}

void ArrowPointer::DestroyInstance()
{
    if (self)
    {
        delete self;
        self = nullptr;
    }
}

void ArrowPointer::Initialize()
{
}

void ArrowPointer::Release()
{
}

void ArrowPointer::Update()
{
    GameObject::Update();
}
