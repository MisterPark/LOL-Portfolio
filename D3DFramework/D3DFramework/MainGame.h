#pragma once


namespace Engine
{
	class MainGame
	{
	private:
		MainGame();
		~MainGame();

	public:
		static MainGame* GetInstance();
		static void Destroy();

		static void Initialize(int screenW, int screenH);

		static void Update();
		static void Release();

		static void Pause();
		static void Resume();
		static void Shutdown();

		static int GetWidth();
		static int GetHeight();

		
		static void LoadUISprite();
		static void LoadAllTextureInFolder(const wstring& _path);

		Triangle* tri = nullptr;
	public:
		int width = dfCLIENT_WIDTH;
		int height = dfCLIENT_HEIGHT;
	};
}


