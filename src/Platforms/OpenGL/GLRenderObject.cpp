#include "GLRenderObject.h"
#include "../../Utils/Debug.h"
namespace Lava {
	namespace OpenGL {
		GLRenderObject::GLRenderObject(Lava::Mesh mesh)
		{
			m_mesh = mesh;
			m_vbo = CreateRef<GLVertexBuffer>(mesh.m_positions, mesh.m_posCount);
			m_ibo = CreateRef<GLIndexBuffer>(mesh.m_indices, mesh.m_indiceCount);
			m_vbo->SetBufferElements(m_mesh.m_bufferLayoutElement,&(m_mesh.m_bufferLayoutCount));
			m_vao = new GLVAO();
			m_vao->AddVertexBufferObject(m_vbo);
			m_vao->SetIndexBuffer(m_ibo);
		}
	}
}