#pragma once
#define dfMAX_BUF_SIZE 4096

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

	static void Print(const char* _text, ...);
	static void PrintLine(const char* _text, ...);

};

