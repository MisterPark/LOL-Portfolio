#pragma once

class EventHandler
{
public:
	EventHandler();
	EventHandler( void(*Func)());
	virtual ~EventHandler() = default;

	void operator()();
	bool operator==(const EventHandler& rhs);
	bool operator!=(const EventHandler& rhs);
	bool operator==(void* ptr);
	bool operator!=(void* ptr);

protected:
	void(*Func)() = nullptr;
	unsigned ID = 0;
private:
	static unsigned uniqueID;
};

class Event
{
public:
	void operator()();
	Event& operator+=(const EventHandler& handler);
	Event& operator-=(const EventHandler& handler);

	void Invoke();
	void AddHandler(const EventHandler& handler);
	void RemoveHandler(const EventHandler& handler);

private:
	list<EventHandler> handlers;
};

