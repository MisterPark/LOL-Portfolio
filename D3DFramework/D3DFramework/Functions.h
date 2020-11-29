#pragma once

template <typename T>
constexpr int MaxOfEnum()
{
	return (int)T::END;
}

template <typename T>
DWORD Safe_Release(T** pointer)
{
	DWORD	dwRefCnt = 0;
	if (NULL != *pointer)
	{
		dwRefCnt = (*pointer)->Release();
		if (dwRefCnt == 0)
			*pointer = NULL;
	}
	return dwRefCnt;
}

template <typename T>
DWORD Safe_AddRef(T** pointer)
{
	DWORD	dwRefCnt = 0;
	if (NULL != *pointer)
		dwRefCnt = (*pointer)->AddRef();

	return dwRefCnt;
}

template <typename T>
void Safe_Single_Destory(T** pointer)
{
	if (NULL != *pointer)
	{
		*pointer->DestroyInstance();
		*pointer = NULL;
	}
}

template <typename T>
void Safe_Delete(T** pointer)
{
	if (NULL != *pointer)
	{
		delete *pointer;
		*pointer = NULL;
	}
}

template <typename T>
void Safe_Delete_Array(T** pointer)
{
	if (NULL != *pointer)
	{
		delete[] *pointer;
		*pointer = NULL;
	}
}