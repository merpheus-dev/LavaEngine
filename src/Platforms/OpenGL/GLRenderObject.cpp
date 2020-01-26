#include "GLRenderObject.h"
#include "../../Utils/Debug.h"
#include "../../Utils/MemoryUtils.h"
namespace Lava {
	namespace OpenGL {
		GLRenderObject::GLRenderObject(Lava::Mesh mesh,Lava::Material material)
		{
			m_mesh = mesh;
			m_material = material;
			m_vao = new GLVAO();

			m_vbo = CreateRef<GLVertexBuffer>(mesh.m_positions, mesh.m_posCount);
			m_vbo->SetBufferElements(m_mesh.m_bufferLayoutElement,&(m_mesh.m_bufferLayoutCount));
			m_vao->AddVertexBufferObject(m_vbo,0);

			m_texCoord = CreateRef<GLVertexBuffer>(m_material.m_uvCoords, m_material.m_uvCoordCount);
			m_texCoord->SetBufferElements(m_mesh.m_bufferLayoutElement, &(m_mesh.m_bufferLayoutCount));
			m_vao->AddVertexBufferObject(m_texCoord,1);

			m_normalBuffer = CreateRef<GLVertexBuffer>(m_mesh.m_normals, m_mesh.m_normCount);
			m_normalBuffer->SetBufferElements(m_mesh.m_bufferLayoutElement, &(m_mesh.m_bufferLayoutCount));
			m_vao->AddVertexBufferObject(m_normalBuffer, 2);

			m_ibo = CreateRef<GLIndexBuffer>(mesh.m_indices, mesh.m_indiceCount);
			m_vao->SetIndexBuffer(m_ibo);
		}
		void GLRenderObject::EnableAttributes()
		{
			for (int i = 0; i < m_mesh.m_bufferLayoutCount; i++)
				glEnableVertexAttribArray(i);
		}
		void GLRenderObject::DisableAttributes()
		{
			for (int i = 0; i < m_mesh.m_bufferLayoutCount; i++)
				glDisableVertexAttribArray(i);
		}
		bool GLRenderObject::HasTexture()
		{
			return m_material.m_mainTexture->valid;
		}
	}
}