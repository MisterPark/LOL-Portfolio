#include "stdafx.h"
#include "ForwardRenderer.h"

Engine::ForwardRenderer::ForwardRenderer(GameObject* const owner, std::wstring const& path):
	Renderer(owner, RendererType::Forward)
{
	effect = RenderManager::LoadEffect(path.c_str());
	mesh = nullptr;
	pass = 0;
}

void Engine::ForwardRenderer::SetValue(const char* parameter, float value)
{
	
	parameterTable[parameter] = make_pair(&typeid(float), Parameter{ value });
}

void Engine::ForwardRenderer::SetValue(const char* parameter, Vector3 const& value)
{
	Parameter param{};
	memcpy(&param.vector4, &value, sizeof(Vector3));
	parameterTable[parameter] = make_pair(&typeid(D3DXVECTOR4), param);

}

void Engine::ForwardRenderer::SetValue(const char* parameter, D3DXVECTOR4 const& value)
{
	Parameter param{};
	memcpy(&param.vector4, &value, sizeof(D3DXVECTOR4));
	parameterTable[parameter] = make_pair(&typeid(D3DXVECTOR4), param);
}

void Engine::ForwardRenderer::SetValue(const char* parameter, Matrix const& value)
{
	Parameter param{};
	memcpy(&param.vector4, &value, sizeof(Matrix));
	parameterTable[parameter] = make_pair(&typeid(Matrix), param);
}

void Engine::ForwardRenderer::SetValue(const char* parameter, IDirect3DTexture9* const value)
{
	Parameter param{};
	param.texture = value;
	parameterTable[parameter] = make_pair(&typeid(IDirect3DTexture9*), param);
}

void Engine::ForwardRenderer::SetDiffuseTextureParam(const char* const parameter)
{
	diffuseTextureHandle = parameter;
}

void Engine::ForwardRenderer::SetPass(int pass)
{
	this->pass = pass;
}

void Engine::ForwardRenderer::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void Engine::ForwardRenderer::Render()
{
	for (auto const& pair: parameterTable)
	{
		std::string const& key = pair.first;
		std::type_info const* type = pair.second.first;
		Parameter const& param = pair.second.second;
		if (*type == typeid(float))
		{
			effect->SetFloat(key.c_str(), param.f32);
		}
		else if (*type == typeid(D3DXVECTOR4))
		{
			effect->SetVector(key.c_str(), (D3DXVECTOR4 const*)param.vector4);
		}
		else if (*type == typeid(Matrix))
		{
			effect->SetMatrix(key.c_str(), (D3DXMATRIX const*)param.matrix);
		}
		else if (*type == typeid(IDirect3DTexture9*))
		{
			effect->SetTexture(key.c_str(), param.texture);
		}
	}
	UINT passCount{};
	int const subsetCount = this->mesh->GetSubsetCount();
	Matrix mViewSpace = Camera::main->GetViewMatrix();
	Matrix mProjSpace = Camera::main->GetProjectionMatrix();
	Matrix mViewProj = mViewSpace * mProjSpace;
	Matrix mWorld = this->transform->GetWorldMatrix();

	effect->SetMatrix("g_mWorld", &mWorld);
	effect->SetMatrix("g_mViewProj", &mViewProj);
	effect->Begin(&passCount, 0);
	effect->BeginPass(pass);
	for (int i = 0; i < subsetCount; ++i)
	{
		IDirect3DTexture9* texture =  this->mesh->GetSubsetTexture(i);
		effect->SetTexture(diffuseTextureHandle.c_str(), texture);
		effect->CommitChanges();
		this->mesh->RenderSubset(i);
	}
	effect->EndPass();
	effect->End();
}

IComponent* Engine::ForwardRenderer::Clone()
{
	return nullptr;
}
