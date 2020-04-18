#pragma once
#include "Transform.h"
#include "MeshRenderer.h"
#include "../Renderer/Mesh.h"
#include "../Renderer/RenderObject.h"
#include "../Renderer/Shader.h"
#include "../Renderer/ShaderBank.h"
#include "../Renderer/MeshMaterialPack.h"
namespace Lava {
	class SceneObject
	{
	public:
		virtual ~SceneObject() = default;
	};
	class Entity :public SceneObject{
	public:
		Transform* transform;
		MeshRenderer* meshRenderer;
		Mesh* mesh;
		Material* material;
		//Entity()
		//{
		//	transform = new Transform();
		//	mesh = new Mesh();
		//	material = new Material();
		//}
		Entity(MeshMaterialPack* _pack)
		{
			transform = new Transform();
			mesh = _pack->mesh;
			material = _pack->material;
		}

		//Entity(glm::vec3 position)
		//{
		//	transform = new Transform(position);
		//	mesh = new Mesh();
		//	material = new Material();
		//}

		Entity(glm::vec3 position, MeshMaterialPack* _pack)
		{
			transform = new Transform(position);
			mesh = _pack->mesh;
			material = _pack->material;
		}

		void SetBufferLayout(std::vector<VertexBufferElement>& bufferElements)
		{
			mesh->m_bufferLayoutElement = &bufferElements[0];
			mesh->m_bufferLayoutCount = bufferElements.size();
		}

		void SetMeshData(std::vector<float>& vertices, std::vector<int>& indices,
			std::vector<VertexBufferElement>& bufferElements) {
			mesh->m_positions = &vertices[0];
			mesh->m_posCount = vertices.size();
			mesh->m_indices = &indices[0];
			mesh->m_indiceCount = indices.size();
			mesh->m_bufferLayoutElement = &bufferElements[0];
			mesh->m_bufferLayoutCount = bufferElements.size();
		}

		MeshRenderer* GetMeshRenderer(Platform platform) {
			if (meshRenderer) return meshRenderer;
			meshRenderer = new MeshRenderer(mesh, material, platform);
			return meshRenderer;
		}
	};
	struct BatchedEntities :SceneObject
	{
		BatchedEntities()
		{
			batch = new std::vector<Entity*>();
		}
		~BatchedEntities()
		{
			
		}
		std::vector<Entity*>* batch;
	};
}