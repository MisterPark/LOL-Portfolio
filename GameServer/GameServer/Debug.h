#pragma once
#include <iostream>
#include <Windows.h>

#define dfMAX_BUF_SIZE 4096

enum class LogLevel
{
	Debug,
	Warning,
	Error,
	System,
};

class Debug
{
private:
	Debug();
	~Debug();

public:
	static Debug* GetInstance();
	
	static void Print(const char* _text, ...);
	static void PrintLine(const char* _text, ...);
	static void Log(LogLevel level, const char* title, const char* format, ...);
	static void Log(const char* title, const char* format, ...);
	static void LogWarning(const char* title, const char* format, ...);
	static void LogError(const char* title, const char* format, ...);
	static void LogSystem(const char* title, const char* format, ...);

private:
	
	char saveDirectory[25] = { 0, };
	WCHAR saveDirectoryW[25] = { 0, };
	DWORD logCount = 0;
public:
	static const LogLevel D = LogLevel::Debug;
	static const LogLevel W = LogLevel::Warning;
	static const LogLevel E = LogLevel::Error;
	static const LogLevel S = LogLevel::System;
};

