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
#include<functional>
namespace PKH
{
	class GameObject;
}
namespace KST
{
	namespace ES
	{
		using namespace PKH;
		class EventArgs
		{
		public:
			virtual ~EventArgs() {}
		};
		class EventHandler
		{
		public:
			virtual ~EventHandler() {}
			virtual void Invoke(GameObject* sender, EventArgs* args) const = 0;
			virtual bool IsEqual (EventHandler const& r) = 0;
		};
		class StaticMethodEventHandler : public EventHandler
		{
		public:
			using DefaultMethodType = void(*)(GameObject*, EventArgs* args);
			StaticMethodEventHandler(DefaultMethodType handler):
				function{handler}
			{

			}
			void Invoke(GameObject* sender, EventArgs* args) const
			{
				function(sender, args);
			}
			virtual bool IsEqual(EventHandler const& r)
			{
				if (typeid(r) != typeid(StaticMethodEventHandler))
				{
					return false;
				}
				return static_cast<StaticMethodEventHandler const&>(r).function == function;
			}
			DefaultMethodType Method()
			{
				return function;
			}
		private:
			DefaultMethodType function;
		};
		class TargetMethodEventHandler:public EventHandler
		{
		public:
			using DefaultMethodType = void(GameObject::*)(GameObject*, EventArgs* args);
			TargetMethodEventHandler(GameObject* target, DefaultMethodType method):
				target{ target },
				method{ method }
			{

			}
			void Invoke(GameObject* sender, EventArgs* args) const
			{
				(target->*method)(sender, args);
			}
			virtual bool IsEqual(EventHandler const& r)
			{
				if (dynamic_cast<TargetMethodEventHandler const*>(&r) == nullptr)
				{
					return false;
				}
				auto const& rhs{ static_cast<TargetMethodEventHandler const&>(r) };

				return rhs.target == target && rhs.method == method;
			}
			GameObject* Target()
			{
				return target;
			}
			DefaultMethodType Method()
			{
				return method;
			}
		private:
			GameObject* target;
			DefaultMethodType method;

		};

		class EventBase
		{
		public:

			virtual ~EventBase()
			{
				for (auto& pair : weakPtrListeners)
				{
					GameObject* target{ pair.first };
					void(GameObject:: * method)(EventBase*) { pair.second };
					(target->*method)(this);
				}
			}
			void Remove(StaticMethodEventHandler::DefaultMethodType method)
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
			void Remove(GameObject* target, TargetMethodEventHandler::DefaultMethodType method)
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
			void RemoveTarget(GameObject* target)
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
			template<typename T>
			void AddWeakRef(T* target, void(T::* method)(EventBase*))
			{
				weakPtrListeners.emplace_back((GameObject*)target, (void(GameObject::*)(EventBase*))(method));
			}
			template<typename T>
			void RemoveWeakRef(T* target)
			{
				auto it = weakPtrListeners.begin();
				auto const end = weakPtrListeners.end();
				while (it != end)
				{
					if (it->first == target)
					{
						it = weakPtrListeners.remove(it);
						continue;
					}
					++it;
				}
			}
		protected:
			std::list<std::pair<GameObject*, void(GameObject::*)(EventBase*)> > weakPtrListeners;
			std::list <std::unique_ptr<EventHandler> > eventHandlers;
		};

		template<typename T,typename EventArgClass>
		struct EventAddMethodParam
		{
			using TargetMethodType = void(T::*)(GameObject*, EventArgClass*);
			EventAddMethodParam(T* target_, TargetMethodType method_):
				target{ target_ },
				method{ method_ }
			{

			}
			T* target;
			TargetMethodType method;
		};
		template<typename T, typename EventArgClass>
		EventAddMethodParam<T, EventArgClass> Handler(T* target, void(T::*method)(GameObject*, EventArgClass*) )
		{
			return EventAddMethodParam<T, EventArgClass>{target, method};
		}
		template<typename EvtArg_>
		using _StaticFunction = void(*)(GameObject*, EvtArg_*);
		template<typename T>
		_StaticFunction<T> Handler(_StaticFunction<T> handler)
		{
			//빈 함수, 멤버함수 핸들러를 만드는 것과 형식을 비슷하게 맞추기 위해 만듦
			return handler;
		}
		template<typename EventArgClass>
		class Event : public EventBase
		{
		public:
			using StaticMethodType = void(*)(GameObject*, EventArgClass*);
			using TargetMethodType = void(GameObject::*)(GameObject*, EventArgClass*);
			template<typename T, typename MethodArgsClass>
			using TargetMethodType2 = void(T::*)(GameObject*, MethodArgsClass*);
			template<typename MethodArgType>
			void AddMethod(_StaticFunction<MethodArgType> staticMethod)
			{
				eventHandlers.push_back(std::unique_ptr< EventHandler>{new StaticMethodEventHandler{ (StaticMethodEventHandler::DefaultMethodType)staticMethod }});
			}
			template<typename T, typename MethodArgType>
			void AddMethod(T* target, TargetMethodType2<T, MethodArgType> method)
			{
				//타입 제약들.
				//멤버함수의 매개인자의 타입은 이 이벤트의 매개인자의 부모여야 한다(그래야 문제가 없다)
				static_assert(std::is_base_of< MethodArgType, EventArgClass>::value, "");
				//이 이벤트의 매개인자는, EventArgs의 파생이여야 한다.
				static_assert(std::is_base_of< EventArgs, EventArgClass>::value, "");
				//타입제약이다. 클래스 타입 T는 GameObject의 파생이여야 한다.
				static_assert(std::is_base_of< PKH::GameObject, T>::value, "Bind Class Type must be drived by 'PKH::GameObject'");
				eventHandlers.push_back(std::unique_ptr< EventHandler>{ new TargetMethodEventHandler{ static_cast<GameObject*>(target),(TargetMethodEventHandler::DefaultMethodType)(TargetMethodType)method }});
				//
				((GameObject*)target)->AddWeak(this);
			}
			template<typename T, typename MethodArgType>
			void operator += (EventAddMethodParam<T, MethodArgType> const& param)
			{
				AddMethod<T, MethodArgType>(param.target, param.method);
			}
			template<typename MethodArgType>
			void operator += (_StaticFunction<MethodArgType> param)
			{
				AddMethod<MethodArgType>(param);
			}
			void Invoke(GameObject* sender, EventArgClass& arg)
			{
				for (auto const& it : eventHandlers)
				{
					it->Invoke(sender, &arg);
				}
			}
		};
	}
}