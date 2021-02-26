#include "stdafx.h"
#include "FileManager.h"
#include <direct.h>

using namespace Engine;

Engine::FileManager* pFileManager = nullptr;

Engine::FileManager::FileManager()
{
}

Engine::FileManager::~FileManager()
{
}

Engine::FileManager * FileManager::GetInstance()
{
	if (pFileManager == nullptr)
	{
		pFileManager = new FileManager;
	}

	return pFileManager;
}

void Engine::FileManager::Destroy()
{
	delete pFileManager;
}

int Engine::FileManager::MakeDirectory(const char * _directory)
{
	int ret = _mkdir(_directory);
	
	if (ret == ENOENT)
	{
		cout << "[Warning] 올바르지 않은 경로입니다." << endl;
	}

	return ret;
}

int Engine::FileManager::MakeDirectory(const wchar_t* _directory)
{
	int ret = _wmkdir(_directory);

	if (ret == ENOENT)
	{
		cout << "[Warning] 올바르지 않은 경로입니다." << endl;
	}
	return ret;
}

void Engine::FileManager::SetDirectory(const char * _directory)
{
	int srcLen = strlen(_directory);
	int cpyLen = (srcLen < (dfMAX_DIRECTORY_LENGTH - 1)) ? srcLen : (dfMAX_DIRECTORY_LENGTH - 1);
	memset(pFileManager->directory,0,dfMAX_DIRECTORY_LENGTH);
	memcpy(pFileManager->directory, _directory, cpyLen);
}

void Engine::FileManager::SetDirectory(const wchar_t* _directory)
{
}

errno_t Engine::FileManager::OpenFile(const char * _mode)
{
	return fopen_s(&pFileManager->file, pFileManager->directory, _mode);
}

void Engine::FileManager::CloseFile()
{
	if (pFileManager->file == nullptr) return;

	fclose(pFileManager->file);
	pFileManager->file = nullptr;
}

size_t Engine::FileManager::ReadFile(void * _buffer, size_t _elementSize, size_t _elementCount)
{
	return fread(_buffer, _elementSize, _elementCount, pFileManager->file);
}

size_t Engine::FileManager::WriteFile(const void * _buffer, size_t _elementSize, size_t _elementCount)
{
	return fwrite(_buffer, _elementSize, _elementCount, pFileManager->file);
}

int Engine::FileManager::Seek(long _offset, int origin)
{
	return fseek(pFileManager->file, _offset, origin);
}
