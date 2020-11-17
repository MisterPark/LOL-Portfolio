#pragma once


namespace PKH
{
	class MainGame
	{
	private:
		MainGame();
		~MainGame();

	public:
		static MainGame* GetInstance();
		static void Destroy();

		static void Initialize();

		static void Update();
		static void Release();

		static void Pause();
		static void Resume();
		static void Shutdown();

		
		static void LoadUISprite();

		Triangle* tri = nullptr;
	};
}


