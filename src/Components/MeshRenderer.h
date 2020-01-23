#pragma once
#include "../Renderer/RenderObject.h"
#include "../Platforms/PlatformInstanceGenerator.h"
namespace Lava {
	class MeshRenderer {
	public:
		MeshRenderer(Mesh* mesh,Material* material, Platform platform)
			:m_mesh(mesh),m_material(material)
		{
			m_renderObject = PlatformInstanceGenerator::GenerateRenderObject(m_mesh, m_material,platform);
		}
		RenderObject* GetRenderObject() {
			return m_renderObject;
		}
	private:
		RenderObject* m_renderObject;
		Mesh* m_mesh;
		Material* m_material;
	};
}