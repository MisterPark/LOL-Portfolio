#pragma once

class EventHandler
{

protected:
	void(*Func)() = nullptr;
};

class Event
{
public:
	
	Event& operator+=(const EventHandler& handler);
	Event& operator-=(const EventHandler& handler);

	void AddHandler(const EventHandler& handler);
	void RemoveHandler(const EventHandler& handler);
};

