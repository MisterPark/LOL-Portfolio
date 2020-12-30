#pragma once


#pragma comment(lib,"winmm")
#pragma comment(lib,"ws2_32")

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <process.h>
#include <map>
#include <list>
#include <queue>

#include "CRingBuffer.h"
#include "CPacket.h"
#include "Protocol.h"
#include "SessionList.h"
#include "CircularList.h"
#include "MemoryPool.h"
#include "IJob.h"
#include "CJob.h"
#include "CJobOnRecv.h"
#include "PacketPool.h"

using namespace std;