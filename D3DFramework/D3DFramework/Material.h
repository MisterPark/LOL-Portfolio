#pragma once
namespace PKH
{
	class Mesh;
}
namespace KST
{
	enum class ShaderType
	{
		Deferred,
		Forward
	};
	class Material
	{
	public:
		virtual ~Material() {}
		virtual void Render() = 0;
		virtual void SetSubset(int index) = 0;
		virtual void SetMesh(PKH::Mesh* mesh) = 0;
	protected:
		ShaderType shaderType;
	};
}