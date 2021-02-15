#pragma once
#include "UI.h"

class PlayerInfoPanel;
namespace PKH
{
	class UIManager
	{
	public:
		static UIManager* GetInstance();
		static void Destroy();

	private:
		UIManager();
		~UIManager();

	public:
		static HRESULT Initialize();
		HRESULT Ready();
		static void Update();
		static void Release();

	private:
		PlayerInfoPanel* pPlayerInfoPanel = nullptr;
	};
}