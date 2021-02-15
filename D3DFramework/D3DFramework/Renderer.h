#pragma once
#include "IComponent.h"
#include <typeinfo>
namespace KST
{
	enum class RendererType :int;
	class Renderer;

	
	class Renderer : public IComponent
	{
	protected:
		Renderer(PKH::GameObject* owner, RendererType rendererType);
	public:
		~Renderer();
		virtual void Render() PURE;
		void SetShadowState(bool use);
		bool IsShadowState();
	protected:
		void AttachToRenderSystem(std::type_info const& infos);
		void DettachToRenderSystem(std::type_info const& infos);
	public:
		RendererType rendererType;
	private:
		bool attached;
		bool shadow;
	};
	template<typename ParentClass, typename DerivedClass>
	class RendererEx : public ParentClass
	{
	protected:
		RendererEx(PKH::GameObject* owner);
	public:
		virtual  ~RendererEx();
		virtual PKH::IComponent* Clone() override;
	private:
	};
	template<typename ParentClass, typename DerivedClass>
	RendererEx<ParentClass, DerivedClass>::RendererEx(PKH::GameObject* owner):
		ParentClass{owner}
	{
		ParentClass::AttachToRenderSystem(typeid(DerivedClass));
	}

	template<typename ParentClass, typename DerivedClass>
	inline RendererEx<ParentClass, DerivedClass>::~RendererEx()
	{
		ParentClass::DettachToRenderSystem(typeid(DerivedClass));
	}
	template<typename ParentClass, typename DerivedClass>
	inline PKH::IComponent* RendererEx<ParentClass, DerivedClass>::Clone()
	{
		return nullptr;
	}
}