#pragma once
#include <string>
#include <Windows.h>
using namespace std;

class TextParser
{
private:
	TextParser();
	~TextParser();
public:
	static TextParser* GetInstance();
	static void DestroyInstance();

	static void Parse(const string& _path);
	static const WCHAR* GetIP();

private:
	string path;
	wstring ip;
};

