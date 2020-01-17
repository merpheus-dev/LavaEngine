#include "GLMeshData.h"
#include "GLConsts.h"
namespace Lava {
	namespace OpenGL {
		GLVertexBuffer::GLVertexBuffer(float* vertex_positions, unsigned int size)
			:m_size(size)
		{
			glGenBuffers(1, &m_bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertex_positions, GL_STATIC_DRAW);
		}
		GLVertexBuffer::~GLVertexBuffer()
		{
			glDeleteBuffers(1, &m_bufferId);
		}
		void GLVertexBuffer::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
		}
		void GLVertexBuffer::UnBind() const
		{
			glBindBuffer(GL_VERTEX_ARRAY, LAVA_BUFFER_CLEAR_ID);
		}

		// Actual buffer content will be delivered in ctor.
		// This is for setting the layout such as position 0,3-texcoord1,2 etc.
		void GLVertexBuffer::SetBufferElements(VertexBufferElement* element,
			int* bufferElementCount)
		{
			m_bufferElement = element;
			m_bufferElementCount = bufferElementCount;
		}


		GLIndexBuffer::GLIndexBuffer(int* indices, unsigned int& count)
			: m_count(count)
		{
			glGenBuffers(1, &m_bufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int),
				indices, GL_STATIC_DRAW);

		}
		GLIndexBuffer::~GLIndexBuffer()
		{
			glDeleteBuffers(1, &m_bufferId);
		}

		void GLIndexBuffer::Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
		}

		void GLIndexBuffer::Unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, LAVA_BUFFER_CLEAR_ID);
		}

		int GLIndexBuffer::GetSize() const
		{
			return sizeof(GLuint) * m_count;
		}
	}
}