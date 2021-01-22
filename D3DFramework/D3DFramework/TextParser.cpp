#include "stdafx.h"
#include "TextParser.h"

TextParser* pTextParser = nullptr;

TextParser::TextParser()
{
}

TextParser::~TextParser()
{
}

TextParser * TextParser::GetInstance()
{
	if (pTextParser == nullptr)
	{
		pTextParser = new TextParser();
	}
	return pTextParser;
}

void TextParser::DestroyInstance()
{
	if (pTextParser)
	{
		delete pTextParser;
		pTextParser = nullptr;
	}
}

void TextParser::Parse(const string & _path)
{
	char buf[16] = {};
	string str;
	FileManager::GetInstance();
	FileManager::SetDirectory(_path.c_str());
	FileManager::OpenFile("rt");
	FileManager::ReadFile(buf, 16, 1);
	str = buf;
	pTextParser->ip.assign(str.begin(), str.end());
	FileManager::CloseFile();
}

const WCHAR * TextParser::GetIP()
{
	return pTextParser->ip.c_str();
}
