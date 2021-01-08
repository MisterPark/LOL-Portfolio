#include "stdafx.h"
#include <iostream>
#include "CPacket.h"


CPacket::CPacket()
{
	Initialize();
}

CPacket::CPacket(int iBufferSize)
{
	Initialize(iBufferSize);
}

CPacket::CPacket(const CPacket& clSrcPacket)
{
	Initialize(clSrcPacket.size);
	memcpy_s(buffer, clSrcPacket.size, clSrcPacket.buffer, clSrcPacket.size);
	write = clSrcPacket.write;
	read = clSrcPacket.read;
}


CPacket::~CPacket()
{
	if (buffer != nullptr)
	{
		delete buffer;
		buffer = nullptr;
	}
}

void CPacket::Initialize(int iBufferSize)
{
	buffer = new char[iBufferSize];
	memset(buffer, 0, iBufferSize);
	size = iBufferSize;
	read = write = 0;
}

void CPacket::Release(void)
{
	delete buffer;
	buffer = nullptr;
}

bool CPacket::Resize(unsigned int resize)
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

void CPacket::Clear(void)
{
	read = write = 0;
}

int CPacket::GetBufferSize(void)
{
	return size;
}

int CPacket::GetUseSize(void)
{
	return useSize;
}

char* CPacket::GetBufferPtr(void)
{
	return buffer;
}

char* CPacket::GetReadPtr(void)
{
	return &buffer[read];
}

char* CPacket::GetWritePtr(void)
{
	return &buffer[write];
}

int CPacket::GetReadPos(void)
{
	return read;
}

int CPacket::GetWritePos(void)
{
	return write;
}

int CPacket::MoveWritePos(int iSize)
{
	if (iSize <= 0) { return 0; }
	if (write + iSize > size)
	{
		int resize = write + iSize;
		resize = resize / 50;
		resize = (resize + 1) * 50;
		Resize(resize);
	}
	useSize += iSize;
	return (write += iSize);
}

int CPacket::MoveReadPos(int iSize)
{
	if (iSize <= 0) { return 0; }
	if (read + iSize > size)
	{
		int resize = write + iSize;
		resize = resize / 50;
		resize = (resize + 1) * 50;
		Resize(resize);
	}
	useSize -= iSize;
	return (read += iSize);
}

void CPacket::SetHeader(WORD& header)
{
	memmove(buffer + 2, buffer, useSize);
	*(WORD*)buffer = header;
	useSize += 2;
}

void CPacket::SetHeader(NetHeader& header)
{
	memmove(buffer + 5, buffer, useSize);
	*(NetHeader*)buffer = header;
	useSize += 5;
}

void CPacket::Encryption()
{
	if (isEncryption == true) return;

	const int Packetsize = useSize;
	unsigned char randKey = rand() % 256;
	unsigned char checkSum = 0;

	for (int i = 0; i < Packetsize; i++)
	{
		checkSum += buffer[i];
	}

	NetHeader header;

	header.code = dfPACKET_CODE;
	header.len = Packetsize;
	header.randKey = randKey;
	header.checkSum = checkSum;

	SetHeader(header);

	unsigned char currentpacket;
	unsigned char prepacket;

	currentpacket = buffer[4] ^ (randKey + 1);
	buffer[4] = currentpacket ^ (fixationKey + 1);
	prepacket = buffer[4];


	for (int i = 1; i < Packetsize + 1; i++)
	{
		currentpacket = buffer[i + 4] ^ (currentpacket + randKey + (i + 1));
		buffer[i + 4] = currentpacket ^ (prepacket + fixationKey + (i + 1));
		prepacket = buffer[i + 4];
	}

	isEncryption = true;
}

bool CPacket::Decryption(NetHeader& header)
{
	if (header.code != dfPACKET_CODE)
	{
		printf("[복호화 실패]패킷코드 다름\n");
		return false;
	}
	const int packetSize = useSize;

	unsigned char randKey = header.randKey;

	unsigned char currentPacket;
	unsigned char prepacket;

	currentPacket = header.checkSum ^ (fixationKey + 1);
	prepacket = currentPacket;

	unsigned char decodeCheckSum = currentPacket ^ (randKey + 1);

	unsigned char checksum = 0;
	char preData;

	////////////////////첫부분/////////////////////////////////

	currentPacket = buffer[0] ^ (fixationKey + 2 + header.checkSum);
	preData = buffer[0];
	buffer[0] = currentPacket ^ (prepacket + randKey + 2);
	prepacket = currentPacket;
	checksum += buffer[0];

	for (int i = 1; i < packetSize; i++)
	{
		currentPacket = buffer[i] ^ (fixationKey + (i + 2) + preData);
		preData = buffer[i];

		buffer[i] = currentPacket ^ (prepacket + randKey + (i + 2));
		prepacket = currentPacket;
		checksum += buffer[i];

	}

	if (checksum != decodeCheckSum)
	{
		printf("[복호화 실패]체크섬 다름\n");
		return false;
	}


	return true;
}

CPacket& CPacket::operator=(const CPacket& pack)
{
	if (buffer != nullptr)
	{
		delete buffer;
		buffer = nullptr;
	}

	int len = pack.size;
	Initialize(len);
	memcpy_s(buffer, len, pack.buffer, len);
	read = pack.read;
	write = pack.write;
	useSize = pack.useSize;

	return *this;
}

CPacket& CPacket::operator<<(bool value)
{
	if (write + sizeof(bool) < size)
	{
		bool* dest = (bool*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(bool));
	}
	return *this;
}

CPacket& CPacket::operator<<(char value)
{
	if (write + sizeof(char) < size)
	{
		char* dest = (char*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(char));
	}
	return *this;
}

CPacket& CPacket::operator<<(short value)
{
	if (write + sizeof(short) < size)
	{
		short* dest = (short*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(short));
	}
	return *this;
}

CPacket& CPacket::operator<<(int value)
{
	if (write + sizeof(int) < size)
	{
		int* dest = (int*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(int));
	}
	return *this;
}

CPacket& CPacket::operator<<(long value)
{
	if (write + sizeof(long) < size)
	{
		long* dest = (long*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(long));
	}
	return *this;
}

CPacket& CPacket::operator<<(float value)
{
	if (write + sizeof(float) < size)
	{
		float* dest = (float*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(float));
	}
	return *this;
}

CPacket& CPacket::operator<<(double value)
{
	if (write + sizeof(double) < size)
	{
		double* dest = (double*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(double));
	}
	return *this;
}

CPacket& CPacket::operator<<(__int64 value)
{
	if (write + sizeof(__int64) < size)
	{
		__int64* dest = (__int64*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(__int64));
	}
	return *this;
}

CPacket& CPacket::operator<<(unsigned char value)
{
	if (write + sizeof(unsigned char) < size)
	{
		unsigned char* dest = (unsigned char*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(unsigned char));
	}
	return *this;
}

CPacket& CPacket::operator<<(unsigned short value)
{
	if (write + sizeof(unsigned short) < size)
	{
		unsigned short* dest = (unsigned short*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(unsigned short));
	}
	return *this;
}

CPacket& CPacket::operator<<(unsigned int value)
{
	if (write + sizeof(unsigned int) < size)
	{
		unsigned int* dest = (unsigned int*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(unsigned int));
	}
	return *this;
}

CPacket& CPacket::operator<<(unsigned long value)
{
	if (write + sizeof(unsigned long) < size)
	{
		unsigned long* dest = (unsigned long*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(unsigned long));
	}
	return *this;
}

CPacket& CPacket::operator<<(unsigned __int64 value)
{
	if (write + sizeof(unsigned __int64) < size)
	{
		unsigned __int64* dest = (unsigned __int64*)&buffer[write];
		*dest = value;
		MoveWritePos(sizeof(unsigned __int64));
	}
	return *this;
}

CPacket& CPacket::operator>>(bool& value)
{
	if (read + sizeof(bool) < size)
	{
		bool* src = (bool*)&buffer[read];
		bool dst;
		memcpy(&dst, src, sizeof(bool));
		value = dst;
		MoveReadPos(sizeof(bool));
	}
	return *this;
}

CPacket& CPacket::operator>>(char& value)
{
	if (read + sizeof(char) < size)
	{
		char* src = (char*)&buffer[read];
		char dst;
		memcpy(&dst, src, sizeof(char));
		value = dst;
		MoveReadPos(sizeof(char));
	}
	return *this;
}

CPacket& CPacket::operator>>(short& value)
{
	if (read + sizeof(short) < size)
	{
		short* src = (short*)&buffer[read];
		short dst;
		memcpy(&dst, src, sizeof(short));
		value = dst;
		MoveReadPos(sizeof(short));
	}
	return *this;
}

CPacket& CPacket::operator>>(int& value)
{
	if (read + sizeof(int) < size)
	{
		int* src = (int*)&buffer[read];
		int dst;
		memcpy(&dst, src, sizeof(int));
		value = dst;
		MoveReadPos(sizeof(int));
	}
	return *this;
}

CPacket& CPacket::operator>>(long& value)
{
	if (read + sizeof(long) < size)
	{
		long* src = (long*)&buffer[read];
		long dst;
		memcpy(&dst, src, sizeof(long));
		value = dst;
		MoveReadPos(sizeof(long));
	}
	return *this;
}

CPacket& CPacket::operator>>(float& value)
{
	if (read + sizeof(float) < size)
	{
		float* src = (float*)&buffer[read];
		float dst;
		memcpy(&dst, src, sizeof(dst));
		value = dst;
		MoveReadPos(sizeof(float));
	}
	return *this;
}

CPacket& CPacket::operator>>(double& value)
{
	if (read + sizeof(double) < size)
	{
		double* src = (double*)&buffer[read];
		double dst;
		memcpy(&dst, src, sizeof(dst));
		value = dst;
		MoveReadPos(sizeof(double));
	}
	return *this;
}

CPacket& CPacket::operator>>(__int64& value)
{
	if (read + sizeof(__int64) < size)
	{
		__int64* src = (__int64*)&buffer[read];
		__int64 dst;
		memcpy(&dst, src, sizeof(dst));
		value = dst;
		MoveReadPos(sizeof(__int64));
	}
	return *this;
}

CPacket& CPacket::operator>>(unsigned char& value)
{
	if (read + sizeof(unsigned char) < size)
	{
		unsigned char* src = (unsigned char*)&buffer[read];
		unsigned char dst;
		memcpy(&dst, src, sizeof(dst));
		value = dst;
		MoveReadPos(sizeof(unsigned char));
	}
	return *this;
}

CPacket& CPacket::operator>>(unsigned short& value)
{
	if (read + sizeof(unsigned short) < size)
	{
		unsigned short* src = (unsigned short*)&buffer[read];
		unsigned short dst;
		memcpy(&dst, src, sizeof(dst));
		value = dst;
		MoveReadPos(sizeof(unsigned short));
	}
	return *this;
}

CPacket& CPacket::operator>>(unsigned int& value)
{
	if (read + sizeof(unsigned int) < size)
	{
		unsigned int* src = (unsigned int*)&buffer[read];
		unsigned int dst;
		memcpy(&dst, src, sizeof(dst));
		value = dst;
		MoveReadPos(sizeof(unsigned int));
	}
	return *this;
}

CPacket& CPacket::operator>>(unsigned long& value)
{
	if (read + sizeof(unsigned long) < size)
	{
		unsigned long* src = (unsigned long*)&buffer[read];
		unsigned long dst;
		memcpy(&dst, src, sizeof(dst));
		value = dst;
		MoveReadPos(sizeof(unsigned long));
	}
	return *this;
}

CPacket& CPacket::operator>>(unsigned __int64 value)
{
	if (read + sizeof(unsigned __int64) < size)
	{
		unsigned __int64* src = (unsigned __int64*)&buffer[read];
		unsigned __int64 dst;
		memcpy(&dst, src, sizeof(dst));
		value = dst;
		MoveReadPos(sizeof(unsigned __int64));
	}
	return *this;
}

int CPacket::Enqueue(char* chpSrc, int iSize)
{
	int re = iSize;
	int free = size - write;
	if (iSize <= 0 || free == 0) { return 0; }

	if (free < iSize)
	{
		Resize(iSize);
		//re = free;
	}

	char* dest = GetWritePtr();
	char* src = chpSrc;

	for (int i = 0; i < re; i++)
	{
		*dest = *src;
		dest++;
		src++;
	}

	MoveWritePos(re);

	return re;
}

int CPacket::Dequeue(char* chpDest, int iSize)
{
	int re = iSize;
	int packSize = GetUseSize();
	if (iSize <= 0 || packSize == 0) { return 0; }

	if (packSize < iSize)
	{
		re = packSize;
	}

	char* dest = chpDest;
	char* src = GetReadPtr();

	for (int i = 0; i < re; i++)
	{
		*dest = *src;
		dest++;
		src++;
	}

	MoveReadPos(re);

	return re;
}
