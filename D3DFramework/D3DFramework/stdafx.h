#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

//=======================================
//  STANDARD
//=======================================
#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <map>
#include <vector>
#include <set>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <tchar.h>
#include <stack>

//=======================================
//  FMOD
//=======================================

#include "FMOD/fmod.h"

#include <d3d9.h>
#include <d3dx9.h>

//=======================================
//  DEBUG
//=======================================

#ifdef _DEBUG

#include <iostream>


#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif
using namespace std;
//=======================================
//  Network
//=======================================

#include "LobbyWindow.h"

#include"MemoryPool.h"
#include "Protocol.h"
#include "CRingBuffer.h"
#include "CPacket.h"
#include "Network.h"
#include "PacketPool.h"
#include "TextParser.h"

//=======================================
//  My Lib
//=======================================

#include "Debug.h"
#include "Define.h"


// DirectX 변형 자료

#include "Point.h"
#include "Vector3.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "transform.h"
#include "Color.h"
#include "Texture.h"
#include "Random.h"

#include "Struct.h"
#include "Functions.h"

#include "PathFinder.h"
#include "Astar.h"

// Base
#include "BaseObject.h"

// 매쉬
#include "Vertex.h"
#include "CustomMesh.h"
#include "Triangle.h"
// 레이어
#include "Layer.h"
// 매니저
#include "SoundManager.h"
#include "MainGame.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "FileManager.h"

#include "CollisionManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "LightManager.h"
#include "LoadManager.h"
#include "NavNodeManager.h"
// 물리
#include "Physics.h"
// 게임 오브젝트
#include "GameObject.h"
#include "Cursor.h"
#include "Camera.h"
#include "Texture.h"
#include "Animation2D.h"

#include "SkillManager.h"

// 
#include "HierarchyLoader.h"
#include "AnimationController.h"

#include "Frustum.h"

#include "NavMesh.h"
#include "NavMeshAgent.h"
#include "GameRenderer.h"


using namespace std;
using namespace PKH;

extern HWND g_hwnd;
extern HINSTANCE g_hInstance;