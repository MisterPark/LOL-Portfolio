
BaseObject::BaseObject(void)
	: refCount(0)
{

}
BaseObject:: ~BaseObject(void)
{

}
unsigned long		BaseObject::AddRef(void)
{
	return refCount++;
}
unsigned long		BaseObject::Release(void)
{
	if (0 == refCount)
	{
		Free();

		delete this;

		return 0;
	}

	return refCount--;
}