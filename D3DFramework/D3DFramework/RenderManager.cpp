#include "stdafx.h"
#include "RenderManager.h"

#include "Texture.h"
using namespace PKH;

PKH::RenderManager* pRenderManager = nullptr;

PKH::RenderManager::RenderManager()
{
	InitializeCriticalSection(&csDevice);
}

PKH::RenderManager::~RenderManager()
{
	DeleteCriticalSection(&csDevice);
	Release();
}

RenderManager* PKH::RenderManager::GetInstance()
{
	if (pRenderManager == nullptr)
	{
		pRenderManager = new RenderManager();
	}
	return pRenderManager;
}

void PKH::RenderManager::Destroy()
{
	if (pRenderManager)
	{
		delete pRenderManager;
		pRenderManager = nullptr;
	}
}

HRESULT PKH::RenderManager::Initialize(int screenW, int screenH)
{
	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	//1.장치의 수준을 조사할 컴객체를 생성. 
	pRenderManager->pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(pRenderManager->pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		// 실패 했을때에 대한 메시지를 넣어줄 것. 
		MessageBoxW(g_hwnd, L"Get DeviceCaps Failed", nullptr, MB_OK);

		return E_FAIL;
	}
	DWORD vp = 0;
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	
	//백 버퍼의 가로 세로 크기. 
	d3dpp.BackBufferWidth = screenW;
	d3dpp.BackBufferHeight = screenH;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;


	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hwnd;
	// 거짓이면 전체화면, 참이면  창모드을 사용하겠다. 
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//3. 조사하고 세팅한 데이터를 가지고 이제 장치를 제어할 컴객체를 생성하자!
	if (FAILED(pRenderManager->pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hwnd, vp | D3DCREATE_MULTITHREADED, &d3dpp, &pRenderManager->pDevice)))
	{
		MessageBoxW(g_hwnd, L"Failed Creating Device", nullptr, MB_OK);
		return E_FAIL;
	}
	if (FAILED(D3DXCreateSprite(pRenderManager->pDevice, &pRenderManager->pSprite)))
	{
		MessageBoxW(g_hwnd, L"Failed Creating Sprite", nullptr, MB_OK);
		return E_FAIL;
	}
	D3DXFONT_DESCW fontInfo;
	ZeroMemory(&fontInfo, sizeof(D3DXFONT_DESCW));
	fontInfo.Height = 25;
	fontInfo.Width = 0;
	fontInfo.Weight = FW_HEAVY;
	fontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(fontInfo.FaceName, L"배달의민족 주아");
	if (FAILED(D3DXCreateFontIndirect(pRenderManager->pDevice, &fontInfo, &pRenderManager->pFont)))
	{
		MessageBoxW(g_hwnd, L"폰트 생성 실패", nullptr, MB_OK);
		return E_FAIL;
	}
	
	if (FAILED(D3DXCreateLine(pRenderManager->pDevice, &pRenderManager->pLine)))
	{
		MessageBoxW(g_hwnd, L"라인 생성 실패", nullptr, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

void PKH::RenderManager::Release()
{
	for (auto pair : pRenderManager->textureMap)
	{
		delete pair.second;
	}

	for (auto pair : pRenderManager->staticMeshMap)
	{
		delete pair.second;
	}

	for (auto pair : pRenderManager->dynamicMeshMap)
	{
		delete pair.second;
	}

	for (auto pair : pRenderManager->terrainMeshMap)
	{
		delete pair.second;
	}

	pRenderManager->textureMap.clear();
	pRenderManager->staticMeshMap.clear();
	pRenderManager->dynamicMeshMap.clear();
	pRenderManager->terrainMeshMap.clear();

	if (pRenderManager->pLine)
	{
		pRenderManager->pLine->Release();
	}
	if (pRenderManager->pFont)
	{
		pRenderManager->pFont->Release();
	}
	if (pRenderManager->pSprite)
	{
		pRenderManager->pSprite->Release();
	}
	if (pRenderManager->pDevice)
	{
		pRenderManager->pDevice->Release();
	}
	if (pRenderManager->pSDK)
	{
		pRenderManager->pSDK->Release();
	}
}

void PKH::RenderManager::Clear()
{
	//EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, Color::Gray.value, 1.f, 0);
	pRenderManager->pDevice->BeginScene();
	//LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::Present(HWND renderTarget)
{
	//EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pDevice->EndScene();
	pRenderManager->pDevice->Present(nullptr, nullptr, renderTarget, nullptr);
	//LeaveCriticalSection(&pRenderManager->csDevice);
}

LPDIRECT3DDEVICE9 PKH::RenderManager::GetDevice()
{
	return pRenderManager->pDevice;
}

LPD3DXSPRITE PKH::RenderManager::GetSprite()
{
	return pRenderManager->pSprite;
}

Texture * PKH::RenderManager::GetTexture(TextureKey _key)
{
	auto find = pRenderManager->textureMap.find(_key);
	if (find == pRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return nullptr;
	}

	return find->second;
}

LPD3DXLINE PKH::RenderManager::GetLine()
{
	return pRenderManager->pLine;
}


HRESULT PKH::RenderManager::LoadSprite(TextureKey spriteKey, const wstring& filePath, DWORD row, DWORD col)
{
	
	auto find = pRenderManager->textureMap.find(spriteKey);

	if (find != pRenderManager->textureMap.end())
	{
		
		return S_OK;
	}

	Texture* tex = new Texture;

	if (FAILED(D3DXGetImageInfoFromFile(filePath.c_str(), &tex->imageInfo)))
	{
		MessageBox(g_hwnd, L"이미지 정보 불러오기 실패", nullptr, MB_OK);
		delete tex;
		//LeaveCriticalSection(&pRenderManager->csDevice);
		return E_FAIL;
	}

	//EnterCriticalSection(&pRenderManager->csDevice);
	if (FAILED(D3DXCreateTextureFromFileExW(
		pRenderManager->pDevice,
		filePath.c_str(),
		tex->imageInfo.Width,
		tex->imageInfo.Height,
		tex->imageInfo.MipLevels,
		0,
		tex->imageInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		&tex->pTexture)))
	{
		wstring errMsg = filePath + L"Create Texture Failed";
		MessageBox(g_hwnd, errMsg.c_str(), nullptr, MB_OK);
		delete tex;
		//LeaveCriticalSection(&pRenderManager->csDevice);
		return E_FAIL;
	}
	//LeaveCriticalSection(&pRenderManager->csDevice);

	tex->rowCount = row;
	tex->colCount = col;

	pRenderManager->textureMap[spriteKey] = tex;
	return S_OK;
}

void PKH::RenderManager::DrawSprite(TextureKey spriteKey, Vector3 pos, int index)
{
	auto find = pRenderManager->textureMap.find(spriteKey);
	if (find == pRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();

	int row = index / tex->colCount;
	int col = index % tex->colCount;

	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = x + w;
	area.bottom = y + h;

	float centerX = float(w >> 1);
	float centerY = float(h >> 1);

	Matrix world, trans;
	D3DXMatrixTranslation(&trans, pos.x, pos.y, 0.f);
	world = trans;

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	pRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(centerX, centerY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawSprite(TextureKey spriteKey, const Transform& transform, int index)
{
	auto find = pRenderManager->textureMap.find(spriteKey);
	if (find == pRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();

	int row = index / tex->colCount;
	int col = index % tex->colCount;

	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = x + w;
	area.bottom = y + h;

	float centerX = float(w >> 1);
	float centerY = float(h >> 1);

	Matrix world, trans, rot, scale, parent;
	D3DXMatrixScaling(&scale, transform.scale.x, transform.scale.y, 0.f);
	D3DXMatrixTranslation(&trans, transform.position.x, transform.position.y, 0.f);
	world = scale * trans;

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	pRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(centerX, centerY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawUI(TextureKey spriteKey, const Transform& transform, int index)
{
	auto find = pRenderManager->textureMap.find(spriteKey);
	if (find == pRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();

	int row = index / tex->colCount;
	int col = index % tex->colCount;

	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = x + w;
	area.bottom = y + h;

	Matrix world, trans, rot, scale, parent;
	D3DXMatrixScaling(&scale, transform.scale.x, transform.scale.y, 0.f);
	D3DXMatrixTranslation(&trans, transform.position.x, transform.position.y , 0.f);
	world = scale * trans;

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	pRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawUI(TextureKey spriteKey, Vector3 pos, int index)
{
	auto find = pRenderManager->textureMap.find(spriteKey);
	if (find == pRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();

	int row = index / tex->colCount;
	int col = index % tex->colCount;

	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = x + w;
	area.bottom = y + h;

	Matrix world, trans;
	D3DXMatrixTranslation(&trans, pos.x, pos.y, 0.f);
	world = trans;

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	pRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawUI(TextureKey spriteKey, Vector3 pos, Vector3 scale, int index)
{
	auto find = pRenderManager->textureMap.find(spriteKey);
	if (find == pRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();

	int row = index / tex->colCount;
	int col = index % tex->colCount;

	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = (x + w);
	area.bottom = y + h;

	Matrix matWorld, matPos, matScale;
	D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.f);
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, 0.f);
	matWorld = matScale * matPos;

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&matWorld);
	pRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawUI(TextureKey spriteKey, Vector3 pos, Vector3 scale, int index, float verticalPer)
{
	auto find = pRenderManager->textureMap.find(spriteKey);
	if (find == pRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();

	int row = index / tex->colCount;
	int col = index % tex->colCount;

	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = (x + w) * verticalPer;
	area.bottom = y + h;

	Matrix matWorld, matPos, matScale;
	D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.f);
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, 0.f);
	matWorld = matScale * matPos;

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&matWorld);
	pRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawUIHorizontal(TextureKey spriteKey, Vector3 pos, Vector3 scale, int index, float horizontalPer)
{
	auto find = pRenderManager->textureMap.find(spriteKey);
	if (find == pRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();

	int row = index / tex->colCount;
	int col = index % tex->colCount;

	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = (x + w);
	area.bottom = (y + h) * horizontalPer;

	Matrix matWorld, matPos, matScale;
	D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.f);
	D3DXMatrixTranslation(&matPos, pos.x, pos.y+h-h*horizontalPer, 0.f);
	matWorld = matScale * matPos;

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&matWorld);
	pRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawCharacter(TextureKey spriteKey, const Transform& transform, DWORD row, DWORD col)
{
	auto find = pRenderManager->textureMap.find(spriteKey);
	if (find == pRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = int(tex->imageInfo.Width / tex->colCount);
	int h = int(tex->imageInfo.Height / tex->rowCount);
	int x = col * w;
	int y = row * h;
	RECT area;
	area.left = x;
	area.top = y;
	area.right = x + w;
	area.bottom = y + h;

	float centerX = float(w >> 1);
	float centerY = float(h >> 1);

	Matrix world, trans, rot, scale, parent;
	D3DXMatrixScaling(&scale, transform.scale.x, transform.scale.y, 0.f);
	D3DXMatrixTranslation(&trans, transform.position.x - Camera::main->GetX(), transform.position.y - Camera::main->GetY(), 0.f);
	world = scale * trans;

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	pRenderManager->pSprite->Draw(tex->pTexture, &area, &Vector3(centerX, h, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);

}

void PKH::RenderManager::DrawImage(TextureKey spriteKey, const Transform& transform)
{
	auto find = pRenderManager->textureMap.find(spriteKey);
	if (find == pRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->imageInfo.Width;
	int h = tex->imageInfo.Height;

	Matrix world, trans, rot, scale, parent;
	D3DXMatrixScaling(&scale, transform.scale.x, transform.scale.y, 0.f);
	D3DXMatrixTranslation(&trans, transform.position.x, transform.position.y, 0.f);
	world = scale * trans;

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	pRenderManager->pSprite->Draw(tex->pTexture, nullptr, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawImage(TextureKey spriteKey, float x, float y, float verticalPer)
{
	auto find = pRenderManager->textureMap.find(spriteKey);
	if (find == pRenderManager->textureMap.end())
	{
		// 로드되지 않은 스프라이트.
		return;
	}

	const Texture* tex = find->second;

	// 스프라이트 한장의 넓이와 높이, 위치
	int w = tex->imageInfo.Width;
	int h = tex->imageInfo.Height;
	RECT rt;
	rt.left = 0;
	rt.top = h-h*verticalPer;
	rt.right = w;
	rt.bottom =  h;
	Matrix world, trans, rot, scale, parent;
	D3DXMatrixTranslation(&trans, x, y, 0.f);
	world = trans;

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	pRenderManager->pSprite->Draw(tex->pTexture, &rt, &Vector3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawFont(const string & text)
{
	Matrix world;
	D3DXMatrixIdentity(&world);

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	pRenderManager->pFont->DrawTextA(pRenderManager->pSprite, text.c_str(), lstrlenA(text.c_str()), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);

}

void PKH::RenderManager::DrawFont(const wstring & text)
{
	Matrix world;
	D3DXMatrixIdentity(&world);
	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	pRenderManager->pFont->DrawTextW(pRenderManager->pSprite, text.c_str(), lstrlen(text.c_str()), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawFont(const wstring & text, float x, float y, D3DXCOLOR color)
{
	Matrix world;
	D3DXMatrixTranslation(&world, x, y, 0.f);
	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	pRenderManager->pFont->DrawTextW(pRenderManager->pSprite, text.c_str(), lstrlen(text.c_str()), nullptr, 0, color);
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawFont(const wstring& text, float x, float y, D3DXCOLOR color, RECT* outRect)
{
	Matrix world;
	D3DXMatrixTranslation(&world, x, y, 0.f);
	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	pRenderManager->pFont->DrawTextW(pRenderManager->pSprite, text.c_str(), lstrlen(text.c_str()), outRect, 0, color);
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawFont(const wstring& text, Vector3 pos, Vector3 scale, D3DXCOLOR color)
{
	
	Matrix matWorld, matPos, matScale;
	D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.f);
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, 0.f);
	matWorld = matScale * matPos;

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&matWorld);
	pRenderManager->pFont->DrawTextW(pRenderManager->pSprite, text.c_str(), lstrlen(text.c_str()), nullptr, 0, color);
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::DrawFont(LPD3DXFONT font, const wstring& text, float x, float y, D3DXCOLOR color)
{
	if (font == nullptr) return;
	Matrix world;
	D3DXMatrixTranslation(&world, x, y, 0.f);

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	font->DrawTextW(pRenderManager->pSprite, text.c_str(), lstrlen(text.c_str()), nullptr, 0, color);
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);

}

void PKH::RenderManager::DrawFont(LPD3DXFONT font, const wstring& text, float x, float y, D3DXCOLOR color, RECT* outRect)
{
	if (font == nullptr) return;
	Matrix world;
	D3DXMatrixTranslation(&world, x, y, 0.f);

	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pRenderManager->pSprite->SetTransform(&world);
	font->DrawTextW(pRenderManager->pSprite, text.c_str(), lstrlen(text.c_str()), outRect, DT_CALCRECT, color);
	pRenderManager->pSprite->End();
	LeaveCriticalSection(&pRenderManager->csDevice);

}

void PKH::RenderManager::DrawLine(float sx, float sy, float ex, float ey)
{
	D3DXVECTOR2 point[2] = {};
	point[0].x = sx;
	point[0].y = sy;
	point[1].x = ex;
	point[1].y = ey;

	pRenderManager->pLine->Begin();
	pRenderManager->pLine->Draw(point, 2, D3DCOLOR_ARGB(255, 0, 0, 0));
	pRenderManager->pLine->End();
}

void PKH::RenderManager::DrawLine(float sx, float sy, float ex, float ey, D3DXCOLOR color)
{
	D3DXVECTOR2 point[2] = {};
	point[0].x = sx;
	point[0].y = sy;
	point[1].x = ex;
	point[1].y = ey;

	pRenderManager->pLine->Begin();
	pRenderManager->pLine->Draw(point, 2, color);
	pRenderManager->pLine->End();
}

HRESULT PKH::RenderManager::LoadTexture(TextureKey key, const wstring& filePath)
{
	auto find = pRenderManager->textureMap.find(key);

	if (find != pRenderManager->textureMap.end()) return S_OK;

	Texture* tex = new Texture;

	if (FAILED(D3DXGetImageInfoFromFile(filePath.c_str(), &tex->imageInfo)))
	{
		MessageBox(g_hwnd, L"이미지 정보 불러오기 실패", nullptr, MB_OK);
		delete tex;
		return E_FAIL;
	}
	EnterCriticalSection(&pRenderManager->csDevice);
	if (FAILED(D3DXCreateTextureFromFileW(pRenderManager->pDevice, filePath.c_str(), &tex->pTexture)))
	{
		LeaveCriticalSection(&pRenderManager->csDevice);
		return E_FAIL;
	}
	LeaveCriticalSection(&pRenderManager->csDevice);
	
	return S_OK;
}

HRESULT PKH::RenderManager::LoadCubeTexture(TextureKey key, const wstring& filePath)
{
	auto find = pRenderManager->textureMap.find(key);

	if (find != pRenderManager->textureMap.end()) return S_OK;

	Texture* tex = new Texture;

	if (FAILED(D3DXGetImageInfoFromFile(filePath.c_str(), &tex->imageInfo)))
	{
		MessageBox(g_hwnd, L"이미지 정보 불러오기 실패", nullptr, MB_OK);
		delete tex;
		return E_FAIL;
	}

	// TODO : 큐브텍스쳐 로드하는거 마지막인자 수정해야할수도있음.
	EnterCriticalSection(&pRenderManager->csDevice);
	if (FAILED(D3DXCreateCubeTextureFromFileW(pRenderManager->pDevice, filePath.c_str(), (LPDIRECT3DCUBETEXTURE9*)&tex->pTexture)))
	{
		LeaveCriticalSection(&pRenderManager->csDevice);
		return E_FAIL;
	}
	LeaveCriticalSection(&pRenderManager->csDevice);
	return S_OK;
}

void PKH::RenderManager::DrawTexture(TextureKey key)
{
	auto find = pRenderManager->textureMap.find(key);

	if (find == pRenderManager->textureMap.end()) return;
	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pDevice->SetTexture(0, find->second->pTexture);
	LeaveCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::LockDevice()
{
	EnterCriticalSection(&pRenderManager->csDevice);
}

void PKH::RenderManager::UnlockDevice()
{
	LeaveCriticalSection(&pRenderManager->csDevice);
}

HRESULT PKH::RenderManager::SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix)
{
	EnterCriticalSection(&pRenderManager->csDevice);
	pRenderManager->pDevice->SetTransform(State, pMatrix);
	LeaveCriticalSection(&pRenderManager->csDevice);
	return E_NOTIMPL;
}

HRESULT PKH::RenderManager::LoadStaticMesh(const WCHAR* pFilePath, const WCHAR* pFileName)
{

	StaticMesh* smesh = new StaticMesh(nullptr);
	HRESULT result = smesh->LoadMesh(pFilePath, pFileName);
	if (result != S_OK)
	{
		delete smesh;
		return result;
	}
	
	// 키생성
	wstring key = L"";
	wstring fileName = pFileName;
	for (int i = 0; i < fileName.length(); i++)
	{
		if (fileName[i] == '.') break;
		key += fileName[i];
	}


	pRenderManager->staticMeshMap[key] = smesh;

	return S_OK;
}

StaticMesh* PKH::RenderManager::CloneStaticMesh(const wstring& key)
{
	auto smesh = pRenderManager->staticMeshMap.find(key);
	if (smesh == pRenderManager->staticMeshMap.end())
	{
		MessageBoxW(g_hwnd, L"로드되지 않은 스태틱 메쉬를 참조하거나 키값이 잘못됨.", L"Error", MB_OK);
		return nullptr;
	}

	return (StaticMesh*)smesh->second->Clone();
}

HRESULT PKH::RenderManager::LoadDynamicMesh(const WCHAR* pFilePath, const WCHAR* pFileName)
{
	DynamicMesh* mesh = new DynamicMesh(nullptr);
	HRESULT result = mesh->LoadMesh(pFilePath, pFileName);
	if (result != S_OK)
	{
		delete mesh;
		return result;
	}

	// 키생성
	wstring key = L"";
	wstring fileName = pFileName;
	for (int i = 0; i < fileName.length(); i++)
	{
		if (fileName[i] == '.') break;
		key += fileName[i];
	}


	pRenderManager->dynamicMeshMap[key] = mesh;

	return S_OK;
}

DynamicMesh* PKH::RenderManager::CloneDynamicMesh(const wstring& key)
{
	auto dmesh = pRenderManager->dynamicMeshMap.find(key);
	if (dmesh == pRenderManager->dynamicMeshMap.end())
	{
		MessageBoxW(g_hwnd, L"로드되지 않은 다이나믹 메쉬를 참조하거나 키값이 잘못됨.", L"Error", MB_OK);
		return nullptr;
	}

	return (DynamicMesh*)dmesh->second->Clone();
}

HRESULT PKH::RenderManager::LoadTerrainMesh(const WCHAR* pFilePath, const WCHAR* pFileName)
{
	TerrainMesh* mesh = new TerrainMesh(nullptr);
	HRESULT result = mesh->LoadMesh(pFilePath, pFileName);
	if (result != S_OK)
	{
		delete mesh;
		return result;
	}

	// 키생성
	wstring key = L"";
	wstring fileName = pFileName;
	for (int i = 0; i < fileName.length(); i++)
	{
		if (fileName[i] == '.') break;
		key += fileName[i];
	}


	pRenderManager->terrainMeshMap[key] = mesh;

	return S_OK;
}

TerrainMesh* PKH::RenderManager::CloneTerrainMesh(const wstring& key)
{
	auto mesh = pRenderManager->terrainMeshMap.find(key);
	if (mesh == pRenderManager->terrainMeshMap.end())
	{
		MessageBoxW(g_hwnd, L"로드되지 않은 터레인 메쉬를 참조하거나 키값이 잘못됨.", L"Error", MB_OK);
		return nullptr;
	}

	return (TerrainMesh*)mesh->second->Clone();
}
