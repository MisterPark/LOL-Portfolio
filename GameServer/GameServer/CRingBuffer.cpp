#include "stdafx.h"
#include "CRingBuffer.h"


CRingBuffer::CRingBuffer()
{
	Initial(DEFALT_SIZE);
}

CRingBuffer::CRingBuffer(int iBufferSize)
{
	Initial(iBufferSize);
}

CRingBuffer::~CRingBuffer()
{
	delete buffer;
}

void CRingBuffer::Initial(int iBufferSize)
{
	size = iBufferSize;
	buffer = new char[size];
	memset(buffer, 0, size);
	front = rear = 0;
	InitializeCriticalSection(&cs);
}

void CRingBuffer::Clear()
{
	front = rear = 0;
}

bool CRingBuffer::isEmpty()
{
	return (front == rear);
}

bool CRingBuffer::Resize(unsigned int resize)
{
	char* rebuf = new char[resize];
	if (rebuf == NULL) { return false; }
	for (unsigned int i = 0; i < resize; i++)
	{
		if (i < size)
		{
			rebuf[i] = buffer[i];
		}
		else
		{
			rebuf[i] = '\0';
		}
	}
	size = resize;

	char* target = buffer;
	delete target;
	buffer = rebuf;

	return true;
}

int CRingBuffer::GetBufferSize(void)
{
	return size;
}

int CRingBuffer::GetUseSize(void)
{
	int r = rear;
	int f = front;
	if (f > r)
	{
		return (size - (f - r));

	}
	return (r - f);
}

int CRingBuffer::GetFreeSize(void)
{
	int re = size - 1;
	int use = GetUseSize();
	re -= use;
	return re;
}

int CRingBuffer::GetDeqSize(void) // 디큐사이즈
{
	int re = size - front;
	int use = GetUseSize();

	if (use > re)
	{
		return re;
	}
	else
	{
		return use;
	}
}

int CRingBuffer::GetEnqSize(void) // 인큐사이즈
{
	int re = 0;
	int lSize = size;
	int lRear = rear;
	int lFront = front;

	if (lFront == 0)
	{
		lSize -= 1;
	}

	if (lFront > lRear)
	{
		re = lFront - lRear - 1;
	}
	else
	{
		re = lSize - lRear;
	}

	if (re < 0)
	{
		return 0;
	}
	return re;

	// 이거 변경해야할듯 GetFreeEnqSize()에서 참고.
	//int re = size - rear;
	//int free = GetFreeSize();

	//if (free > re)
	//{
	//	return re;
	//}
	//else
	//{
	//	return free;
	//}
}

int CRingBuffer::Enqueue(char* chpData, int iSize)
{
	if (iSize <= 0) { return 0; }

	char* pData = chpData;
	char* pRear = GetRearBufferPtr();
	char* pBuff = GetBufferPtr();
	int len = iSize;
	int free = 0;
	int part = 0;

	GetFreeEnqSize(&free, &part);

	if (free <= 0) { return 0; }

	if (free < iSize) { len = free; }

	if (len > part)
	{
		memcpy(pRear, pData, part);
		memcpy(pBuff, &pData[part], int(len - part));
	}
	else
	{
		memcpy(pRear, pData, len);
	}

	MoveRear(len);

	return len;
}

int CRingBuffer::Dequeue(char* chpDest, int iSize)
{
	if (iSize <= 0) { return 0; }

	int len = iSize;
	int use = 0;
	int part = 0;

	char* pDest = chpDest;
	char* pFront = GetFrontBufferPtr();
	char* pBuff = GetBufferPtr();

	GetUseDeqSize(&use, &part);

	if (use < iSize) { len = use; }

	if (len > part)
	{
		memcpy(pDest, pFront, part);
		memcpy(&pDest[part], pBuff, int(len - part));
	}
	else
	{
		memcpy(pDest, pFront, len);
	}

	MoveFront(len);

	return len;
}

int CRingBuffer::Peek(char* chpDest, int iSize)
{
	if (iSize <= 0) { return 0; }

	int len = iSize;
	int use = 0;
	int part = 0;

	char* pDest = chpDest;
	char* pFront = GetFrontBufferPtr();
	char* pBuff = GetBufferPtr();

	GetUseDeqSize(&use, &part);

	if (use < iSize) { len = use; }

	if (len > part)
	{
		memcpy(pDest, pFront, part);
		memcpy(&pDest[part], pBuff, len - part);
	}
	else
	{
		memcpy(pDest, pFront, len);
	}

	return len;
}

void CRingBuffer::MoveRear(int iSize)
{
	int re = rear += iSize;
	rear = re % size;
}

void CRingBuffer::MoveFront(int iSize)
{
	int re = front += iSize;
	front = re % size;
}

void CRingBuffer::ClearBuffer(void)
{
	front = rear = 0;
}

char* CRingBuffer::GetFrontBufferPtr(void)
{
	return &buffer[front];
}

char* CRingBuffer::GetRearBufferPtr(void)
{
	return &buffer[rear];
}

char* CRingBuffer::GetBufferPtr(void)
{
	return buffer;
}

void CRingBuffer::Lock()
{
	EnterCriticalSection(&cs);
}

void CRingBuffer::Unlock()
{
	LeaveCriticalSection(&cs);
}

void CRingBuffer::GetFreeEnqSize(int* outFree, int* outEnq)
{
	int lRear = rear;
	int lFront = front;
	int use = 0;
	int enq = 0;
	int free = 0;

	// use
	if (lFront > lRear)
	{
		use = (size - (lFront - lRear));
	}
	else
	{
		use = (lRear - lFront);
	}

	//free
	free = (size - 1) - use;

	// enq
	int temp = size;

	if (lFront == 0)
	{
		temp -= 1;
	}

	if (lFront > lRear)
	{
		enq = lFront - lRear - 1;
	}
	else
	{
		enq = temp - lRear;
	}

	if (enq <= 0)
	{
		enq = 0;
	}

	*outFree = free;
	*outEnq = enq;

}

void CRingBuffer::GetUseDeqSize(int* outUse, int* outDeq)
{
	int lRear = rear;
	int lFront = front;
	int use = 0;
	int deq = 0;

	if (lFront > lRear)
	{
		use = (size - (lFront - lRear));
	}
	else
	{
		use = (lRear - lFront);
	}

	int temp = size - lFront;

	if (use > temp)
	{
		deq = temp;
	}
	else
	{
		deq = use;
	}

	*outUse = use;
	*outDeq = deq;
}