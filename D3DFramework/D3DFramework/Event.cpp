#include "stdafx.h"
#include "Event.h"

unsigned EventHandler::uniqueID = 0;

EventHandler::EventHandler()
{
    ID = uniqueID++;
}

EventHandler::EventHandler(void(*Func)())
{
    ID = uniqueID++;
    this->Func = Func;
}

void EventHandler::operator()()
{
    if(Func != nullptr)
        Func();
}

bool EventHandler::operator==(const EventHandler& rhs)
{
    return (this->ID == rhs.ID);
}

bool EventHandler::operator!=(const EventHandler& rhs)
{
    return (this->ID != rhs.ID);
}

bool EventHandler::operator==(void* ptr)
{
    return (this->Func == ptr);
}

bool EventHandler::operator!=(void* ptr)
{
    return (this->Func != ptr);
}

//============================================================
void Event::operator()()
{
}

Event& Event::operator+=(const EventHandler& handler)
{
    AddHandler(handler);
    return *this;
}

Event& Event::operator-=(const EventHandler& handler)
{
    RemoveHandler(handler);
    return *this;
}

void Event::Invoke()
{
    for (auto& handler : handlers)
    {
        handler();
    }
}

void Event::AddHandler(const EventHandler& handler)
{
    handlers.push_back(handler);
}

void Event::RemoveHandler(const EventHandler& handler)
{
    auto iter = handlers.begin();
    auto end = handlers.end();
    for (; iter != end; ++iter)
    {
        if ((*iter) == handler)
        {
            iter = handlers.erase(iter);
            break;
        }
    }
    
}
