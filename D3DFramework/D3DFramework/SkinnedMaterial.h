#pragma once
#include "Material.h"
namespace KST
{
	class SkinnedMeshMaterial : public Material
	{
	public:
		~SkinnedMeshMaterial();
		virtual void Render() override;
		virtual void SetSubset(int index) override;
		virtual void SetMesh(PKH::Mesh* mesh) override;
		void		SetMaterial(Material* material);
	protected:
		ShaderType shaderType;
		Material* material;
		PKH::Mesh* mesh;
	};
}