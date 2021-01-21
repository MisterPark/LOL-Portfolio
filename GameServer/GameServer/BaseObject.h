#pragma once
class BaseObject
{
protected:
	inline explicit BaseObject(void);
	inline virtual ~BaseObject(void);

public:
	inline unsigned long		AddRef(void);
	inline unsigned long		Release(void);

private:
	unsigned long			refCount;

public:
	inline virtual void Free(void) = 0;
};

#include "BaseObject.inl"