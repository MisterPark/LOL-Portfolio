#pragma once
#include <iostream>
#include "CircularList.h"

#define dfMEMORYPOOL_DEFAULT_CHUNK_SIZE 500

//typedef int T;
template<class T>
class MemoryPool
{
public:
	template <class T>
	class Chunk
	{
	public:
		struct Block
		{
			T data;
			long refCount = 0;
			LPVOID checkPointer = nullptr;
		};

		Chunk(unsigned chunkSize, bool isPlacementNew)
		{
			pData = new Block[chunkSize];
			Initialize(chunkSize, isPlacementNew);
		}
		~Chunk()
		{
			if (isPlacementNew)
			{
				for (int i = 0; i < chunkSize; i++)
				{
					pData[i].~Block();
				}
			}
			delete[] pData;
		}

		void Initialize(unsigned chunkSize, bool isPlacementNew)
		{	
			this->chunkSize = chunkSize;
			this->allocCount = 0;
			this->freeCount = 0;
			this->isPlacementNew = isPlacementNew;
		}

		T* Alloc()
		{
			if (allocCount == chunkSize) return nullptr;
			
			int index = InterlockedIncrement(&allocCount);
			Block* pBlock = &pData[index - 1];
			
			if (isPlacementNew)
			{
				new(pBlock)Block;
			}

			pBlock->refCount = 1;
			pBlock->checkPointer = this;
			
			return (T*)pBlock;
		}

		// Return :
		//	TRUE : 청크 내의 모든 데이터를 Free 했음.
		//	FALSE : 나머지
		bool Free(T* outData)
		{
			Block* freeData = (Block*)outData;
			if (freeData->checkPointer != this)
			{
				printf("[오류] Chunk Pointer 불일치\n");
				return false;
			}
			
			if (InterlockedDecrement(&freeData->refCount) != 0)
			{
				return false;
			}
			unsigned freeCnt = InterlockedIncrement(&freeCount);
			if (freeCnt == chunkSize-1) return true;

			return false;
		}

		long 

		unsigned GetAllocCount()
		{
			return this->allocCount;
		}

	private:
		Block* pData = nullptr;
		unsigned allocCount = 0;
		unsigned freeCount = 0;
		unsigned chunkSize = 0;
		bool isPlacementNew = false;
	};

	// 노드
	struct Node
	{
		T data;
		long refCount;
		LPVOID* checkPointer = nullptr;
	};

	MemoryPool(unsigned chunkCount, unsigned chunkSize, bool isPlacementNew)
	{
		this->tlsIndex = TlsAlloc();
		this->chunkSize = chunkSize;
		this->isPlacementNew = isPlacementNew;
		this->chunkCount = chunkCount;
		this->chunkList = new CircularList<Chunk<T>*>(chunkCount);

		Upsizing();
	}

	~MemoryPool()
	{
		TlsFree(tlsIndex);
	}

	T* Alloc()
	{
		Chunk<T>* pChunk = (Chunk<T>*)TlsGetValue(tlsIndex);
		T* pData = nullptr;

		if (pChunk == nullptr || pChunk->GetAllocCount() == chunkSize) // 처음 할당시, 이전 청크 모두 사용시
		{
			if (chunkList->IsEmpty()) 
				Upsizing();

			chunkList->PopFront(&pChunk);
			new (pChunk)Chunk<T>{chunkSize, isPlacementNew};
			TlsSetValue(tlsIndex, (LPVOID)pChunk);
		}

		pData = pChunk->Alloc();
		if (pData == nullptr) // 청크에서 모두 할당한 상태
		{
			TlsSetValue(tlsIndex, nullptr); // nullptr 로 초기화
			pData = Alloc();
		}
		return pData;
	}

	bool Free(T* data)
	{
		if (data == nullptr) return false;

		Node* pNode = (Node*)data;
		Chunk<T>* pChunk = (Chunk<T>*)pNode->checkPointer;
		if (pChunk->Free(data))
		{
			pChunk->Initialize(chunkSize, isPlacementNew);
			chunkList->PushFront(pChunk);
			return true;
		}
		return false;
	}

	long AddRefCount(T* data)
	{
		if (data == nullptr) return -1;

		Node* pNode = (Node*)data;
		return InterlockedIncrement(&pNode->refCount);
	}

	int GetMPSize()
	{
		return chunkList->GetUsedSize();
	}

private:

	void Upsizing()
	{
		for (int i = 0; i < chunkCount; i++)
		{
			Chunk<T>* pChunk = new Chunk<T>(chunkSize, isPlacementNew);
			chunkList->PushBack(pChunk);
		}
	}

	
private:
	CircularList<Chunk<T>*>* chunkList;
	DWORD tlsIndex;
	unsigned chunkSize = dfMEMORYPOOL_DEFAULT_CHUNK_SIZE;
	unsigned chunkCount = dfMEMORYPOOL_DEFAULT_CHUNK_SIZE;
	bool isPlacementNew = false;
	

	
};
