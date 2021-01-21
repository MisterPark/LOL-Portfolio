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
#include <string>
#include <set>

#include "Vector3.h"

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
#include "CNetwork.h"


//=======================================
//  My Lib
//=======================================

#include "Debug.h"
#include "Define.h"

// DirectX 변형 자료

#include "Point.h"

#include "Matrix.h"
#include "Quaternion.h"
#include "transform.h"
#include "Color.h"
#include "Random.h"

#include "Function.h"
#include "Struct.h"

#include "PathFinder.h"
#include "Astar.h"

#include "BaseObject.h"

// 매쉬
#include "Vertex.h"
#include "CustomMesh.h"
#include "Triangle.h"
// 레이어
#include "Layer.h"
// 매니저
#include "ObjectManager.h"
#include "RenderManager.h"
#include "FileManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
// 물리
#include "Physics.h"
// 게임 오브젝트
#include "GameObject.h"

#include "HierarchyLoader.h"
#include "AnimationController.h"


#include "NavMesh.h"
#include "NavMeshAgent.h"




using namespace std;
using namespace PKH;

extern HWND g_hwnd;