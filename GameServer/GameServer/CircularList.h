#pragma once
#include<iostream>
#include<Windows.h>

#define dfARRAY_UNIT_SIZE 1000
//typedef int T;
template <class T>
class CircularList
{
public:
	CircularList(int size = dfARRAY_UNIT_SIZE)
	{
		InitializeSRWLock(&srwlock);
		int s = size;
		if (size <= 0)
			s = dfARRAY_UNIT_SIZE;
		pData = (T*)malloc(sizeof(T) * s);
		this->totalSize = s;
	}

	~CircularList()
	{
		free(pData);
	}

	int GetUsedSize()
	{
		return useSize;
	}

	bool IsEmpty()
	{
		return (useSize == 0);
	}

	bool IsFull()
	{
		return ((totalSize-1) == useSize);
	}

	void Resize(int unit = dfARRAY_UNIT_SIZE)
	{
		int newSize = totalSize + unit;
		T* newData = (T*)malloc(sizeof(T) * newSize);
		if (newData == nullptr)
		{
			printf("Array : Memory Alloc Failed\n");
			return;
		}
		
		if (front < back)
		{
			memcpy(newData, pData, sizeof(T) * useSize);
		}
		else if (front > back)
		{
			T* oldBuff = &pData[front];
			T* newBuff = newData;

			int size1 = (totalSize - front);
			int size2 = back;

			memcpy(newBuff, oldBuff, size1 *sizeof(T));

			newBuff += size1;
			oldBuff = pData;
			memcpy(newBuff, oldBuff, size2 * sizeof(T));

			front = 0;
			back = useSize;
		}

		totalSize += unit;

		T* target = pData;
		free(target);
		pData = newData;

	}

	void PushFront(T data)
	{
		AcquireSRWLockExclusive(&srwlock);
		if (IsFull()) Resize();

		int index = MoveFront(-1);
		pData[index] = data;
		ReleaseSRWLockExclusive(&srwlock);
	}

	void PushBack(T data)
	{
		AcquireSRWLockExclusive(&srwlock);
		if (IsFull()) Resize();

		pData[back] = data;
		MoveBack(1);
		ReleaseSRWLockExclusive(&srwlock);
	}

	bool PopFront(T* outData = nullptr)
	{
		AcquireSRWLockExclusive(&srwlock);
		if (IsEmpty()) return false;

		if(outData != nullptr)
			*outData = pData[front];
		MoveFront(1);
		ReleaseSRWLockExclusive(&srwlock);

		return true;
	}

	bool PopBack(T* outData = nullptr)
	{
		AcquireSRWLockExclusive(&srwlock);
		if (IsEmpty()) return false;

		int index = MoveBack(-1);
		if(outData != nullptr)
			*outData = pData[index];
		ReleaseSRWLockExclusive(&srwlock);
		
		return true;
	}

	void Enqueue(T data)
	{
		PushBack(data);
	}

	bool Dequeue(T* outData)
	{
		return PopFront(outData);
	}

	void Push(T data)
	{
		PushFront(data);
	}

	bool Pop(T* outData)
	{
		return PopFront(outData);
	}

	void Print()
	{
		int index = front;
		int value = 0;
		printf("===============================\n[");
		for (int i = 0; i < useSize; i++)
		{
			value = (int)pData[index];
			printf("%d ", value);
			AddIndex(&index);
		}
		printf("]\n===============================\n");
	}

private:

	int MoveFront(int length)
	{
		int temp = (front + length);
		if (temp >= totalSize)
			temp %= totalSize;
		else if (temp < 0)
			temp = totalSize + temp;
		front = temp;
		useSize -= length;

		return temp;
	}

	int MoveBack(int length)
	{
		int temp = (back + length);
		if (temp >= totalSize)
			temp %= totalSize;
		else if (temp < 0)
			temp = totalSize + temp;
		back = temp;
		useSize += length;

		return temp;
	}

	void AddIndex(int* outIndex)
	{
		int temp = *outIndex + 1;
		temp %= totalSize;
		*outIndex = temp;
	}

private:
	T* pData = nullptr;
	int front = 0;
	int back = 0;
	int totalSize = 0;
	int useSize = 0;
	SRWLOCK srwlock;
};