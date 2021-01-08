#pragma once
#include "CPacket.h"
#include "CircularList.h"
#include "MemoryPool.h"

class PacketPool
{
public:
private:
	PacketPool(int chunk, int size, bool isPlacement);
	~PacketPool();

public:
	static PacketPool* GetInstance();
	static CPacket* Alloc();
	static bool Free(CPacket* pPacket);
	static long AddRefCount(CPacket* pPacket);


private:
	MemoryPool<CPacket>* memPool;
	bool isPlacement = false;
};

