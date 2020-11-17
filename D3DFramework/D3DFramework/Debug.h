#pragma once
class Debug
{
private:
	Debug();
	~Debug();

public:
	static Debug* GetInstance();
	static void Destroy();

	static void Initialize();
	static void Release();

	
};

