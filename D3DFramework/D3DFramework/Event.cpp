#include "stdafx.h"
#include "Event.h"

//unsigned EventHandler::uniqueID = 0;
//
//EventHandler::EventHandler()
//{
//    ID = uniqueID++;
//}
//
//EventHandler::EventHandler(void(*Func)())
//{
//    ID = uniqueID++;
//    this->Func = Func;
//}
//
//void EventHandler::operator()()
//{
//    if(Func != nullptr)
//        Func();
//}
//
//bool EventHandler::operator==(const EventHandler& rhs)
//{
//    return (this->ID == rhs.ID);
//}
//
//bool EventHandler::operator!=(const EventHandler& rhs)
//{
//    return (this->ID != rhs.ID);
//}
//
//bool EventHandler::operator==(void* ptr)
//{
//    return (this->Func == ptr);
//}
//
//bool EventHandler::operator!=(void* ptr)
//{
//    return (this->Func != ptr);
//}
//
////============================================================
//void Event::operator()()
//{
//}
//
//Event& Event::operator+=(const EventHandler& handler)
//{
//    AddHandler(handler);
//    return *this;
//}
//
//Event& Event::operator-=(const EventHandler& handler)
//{
//    RemoveHandler(handler);
//    return *this;
//}
//
//void Event::Invoke()
//{
//    for (auto& handler : handlers)
//    {
//        handler();
//    }
//}
//
//void Event::AddHandler(const EventHandler& handler)
//{
//    handlers.push_back(handler);
//}
//
//void Event::RemoveHandler(const EventHandler& handler)
//{
//    auto iter = handlers.begin();
//    auto end = handlers.end();
//    for (; iter != end; ++iter)
//    {
//        if ((*iter) == handler)
//        {
//            iter = handlers.erase(iter);
//            break;
//        }
//    }
//    
//}
namespace Engine
{
#pragma region  StaticMethodEventHandler impl
        StaticMethodEventHandler::StaticMethodEventHandler(DefaultMethodType handler) :
            function{ handler }
        {

        }
        void StaticMethodEventHandler::Invoke(GameObject* sender, EventArgs* args) const
        {
            function(sender, args);
        }
        bool StaticMethodEventHandler::IsEqual(EventHandler const& r)
        {
            if (typeid(r) != typeid(StaticMethodEventHandler))
            {
                return false;
            }
            return static_cast<StaticMethodEventHandler const&>(r).function == function;
        }
        auto StaticMethodEventHandler::Method()->DefaultMethodType
        {
            return function;
        }
#pragma endregion

#pragma region TargetMethodEventHandler impl
        TargetMethodEventHandler::TargetMethodEventHandler(GameObject* target, DefaultMethodType method) :
            target{ target },
            method{ method }
        {

        }
        void TargetMethodEventHandler::Invoke(GameObject* sender, EventArgs* args) const
        {
            (target->*method)(sender, args);
        }
        bool TargetMethodEventHandler::IsEqual(EventHandler const& r)
        {
            if (dynamic_cast<TargetMethodEventHandler const*>(&r) == nullptr)
            {
                return false;
            }
            auto const& rhs{ static_cast<TargetMethodEventHandler const&>(r) };

            return rhs.target == target && rhs.method == method;
        }
        GameObject* TargetMethodEventHandler::Target()
        {
            return target;
        }
        auto TargetMethodEventHandler::Method()->DefaultMethodType
        {
            return method;
        }
#pragma endregion

        
        EventBase::~EventBase()
        {
            for (auto& pair : weakPtrListeners)
            {
                GameObject* target{ pair.first };
                void(GameObject:: * method)(EventBase*) { pair.second };
                (target->*method)(this);
            }
        }

        void EventBase::Remove(StaticMethodEventHandler::DefaultMethodType method)
        {
            auto it{ eventHandlers.begin() };
            auto const end{ eventHandlers.end() };
            while (it != end)
            {
                if (typeid(*it->get()).before(typeid(StaticMethodEventHandler)))
                {
                    auto* handler{ static_cast<StaticMethodEventHandler*>(it->get()) };
                    if (handler->Method() == method)
                    {
                        it = eventHandlers.erase(it);
                        continue;
                    }
                }
                ++it;
            }
        }

        void EventBase::Remove(GameObject* target, TargetMethodEventHandler::DefaultMethodType method)
        {
            auto it{ eventHandlers.begin() };
            auto const end{ eventHandlers.end() };
            while (it != end)
            {
                if (typeid(*it->get()) == typeid(TargetMethodEventHandler))
                {
                    auto* handler{ static_cast<TargetMethodEventHandler*>(it->get()) };
                    if (handler->Target() == target &&
                        handler->Method() == method)
                    {
                        it = eventHandlers.erase(it);
                        continue;
                    }
                }
                ++it;
            }
        }

        void EventBase::RemoveTarget(GameObject* target)
        {
            auto it{ eventHandlers.begin() };
            auto const end{ eventHandlers.end() };
            while (it != end)
            {
                if (typeid(*it->get()) == typeid(TargetMethodEventHandler))
                {
                    auto* handler{ static_cast<TargetMethodEventHandler*>(it->get()) };
                    if (handler->Target() == target)
                    {
                        it = eventHandlers.erase(it);
                        continue;
                    }
                }
                ++it;
            }
        }

}