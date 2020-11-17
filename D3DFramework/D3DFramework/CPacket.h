#pragma once


class CPacket
{
public:
	enum en_Packet
	{
		eBUFFER_DEFAULT = 10000
	};
	CPacket();
	CPacket(int iBufferSize);
	CPacket(const CPacket &clSrcPacket);
	virtual ~CPacket();

protected:
	void Initial(int iBufferSize = eBUFFER_DEFAULT);
	void Release(void);
	bool Resize(unsigned int resize);

public:
	void Clear(void);
	int GetBufferSize(void);
	int GetPacketSize(void);
	char* GetBufferPtr(void);
	char* GetReadPtr(void);
	char* GetWritePtr(void);
	int GetReadPos(void);
	int GetWritePos(void);
	int MoveWritePos(int iSize);
	int MoveReadPos(int iSize);

	CPacket &operator = (const CPacket &pack);

	CPacket &operator << (bool value);
	CPacket &operator << (char value);
	CPacket &operator << (short	value);
	CPacket &operator << (int value);
	CPacket &operator << (long value);
	CPacket &operator << (float	value);
	CPacket &operator << (double value);
	CPacket &operator << (__int64 value);
	CPacket &operator << (unsigned char value);
	CPacket &operator << (unsigned short value);
	CPacket &operator << (unsigned int value);
	CPacket &operator << (unsigned long value);

	CPacket &operator >> (bool	&value);
	CPacket &operator >> (char	&value);
	CPacket &operator >> (short	&value);
	CPacket &operator >> (int	&value);
	CPacket &operator >> (long	&value);
	CPacket &operator >> (float	&value);
	CPacket &operator >> (double &value);
	CPacket &operator >> (__int64 &value);
	CPacket &operator >> (unsigned char	&value);
	CPacket &operator >> (unsigned short &value);
	CPacket &operator >> (unsigned int &value);
	CPacket &operator >> (unsigned long &value);

	int Enqueue(char* chpSrc, int iSize);
	int Dequeue(char* chpDest, int iSize);

protected:
	char* buffer = nullptr;
	unsigned int read = 0;
	unsigned int write = 0;
	unsigned int size = 0;
};

