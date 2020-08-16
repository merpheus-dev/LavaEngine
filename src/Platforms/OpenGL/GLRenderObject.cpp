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

			m_vbo = CreateRef<GLVertexBuffer>(m_mesh.m_positions, m_mesh.m_posCount);
			m_vbo->SetBufferElements(m_mesh.m_bufferLayoutElement,&(m_mesh.m_bufferLayoutCount));
			m_vao->AddVertexBufferObject(m_vbo,0);

			m_texCoord = CreateRef<GLVertexBuffer>(m_mesh.m_uvCoords, m_mesh.m_uvCoordCount);
			m_texCoord->SetBufferElements(m_mesh.m_bufferLayoutElement, &(m_mesh.m_bufferLayoutCount));
			m_vao->AddVertexBufferObject(m_texCoord,1);

			m_normalBuffer = CreateRef<GLVertexBuffer>(m_mesh.m_normals, m_mesh.m_normCount);
			m_normalBuffer->SetBufferElements(m_mesh.m_bufferLayoutElement, &(m_mesh.m_bufferLayoutCount));
			m_vao->AddVertexBufferObject(m_normalBuffer, 2);

			m_tangentBuffer = CreateRef<GLVertexBuffer>(m_mesh.m_tangents, m_mesh.m_tangentCount);
			m_tangentBuffer->SetBufferElements(m_mesh.m_bufferLayoutElement, &(m_mesh.m_bufferLayoutCount));
			m_vao->AddVertexBufferObject(m_tangentBuffer, 3);

			m_ibo = CreateRef<GLIndexBuffer>(m_mesh.m_indices, m_mesh.m_indiceCount);
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
			if (m_material.m_mainTexture == nullptr) return false;
			return m_material.m_mainTexture->valid;
		}

		bool GLRenderObject::HasNormalMap()
		{
			if (m_material.m_nrmTexture == nullptr) return false;
			return m_material.m_nrmTexture->valid;
		}

		bool GLRenderObject::HasEmissionMap()
		{
			if(m_material.emissionMap==nullptr) return false;
			return m_material.emissionMap->valid;
		}
	}
}