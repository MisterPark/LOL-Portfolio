#include "stdafx.h"
#include "PacketPool.h"

static PacketPool* instance = nullptr;

PacketPool::PacketPool(int chunk, int size, bool isPlacement)
{
	memPool = new MemoryPool<CPacket>(chunk, size, isPlacement);
	this->isPlacement = isPlacement;
}

PacketPool::~PacketPool()
{
	delete instance;
}

PacketPool* PacketPool::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new PacketPool(100,100, true);
	}

	return instance;
}

CPacket* PacketPool::Alloc()
{
	return instance->memPool->Alloc();
}

bool PacketPool::Free(CPacket* pPacket)
{
	return instance->memPool->Free(pPacket);
}

long PacketPool::AddRefCount(CPacket* pPacket)
{
	return instance->memPool->AddRefCount(pPacket);
}
