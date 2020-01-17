#include "GLVAO.h"
#include "GLConsts.h"
namespace Lava
{
	namespace OpenGL
	{
		GLVAO::GLVAO()
		{
			glGenVertexArrays(1, &m_vaoId);
		}
		GLVAO::~GLVAO()
		{
			glDeleteVertexArrays(1, &m_vaoId);
		}
		void GLVAO::Bind() const
		{
			glBindVertexArray(m_vaoId);
		}

		void GLVAO::Unbind() const
		{
			glBindVertexArray(LAVA_BUFFER_CLEAR_ID);
		}

		//To-Do: Replace GL_FLOAT with agnostic type in VertexBufferElement
		void GLVAO::AddVertexBufferObject(const std::shared_ptr<VertexBuffer>& vertexBuffer)
		{
			glBindVertexArray(m_vaoId);
			vertexBuffer->Bind();

			VertexBufferElement* bufferElements = vertexBuffer->GetBufferElements();
			for (int i = 0; i < vertexBuffer->GetBufferElementCount(); i++) 
			{
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, bufferElements[i].uniform_count, GL_FLOAT, GL_FALSE,
										0, (const void*)0);

			}

			m_vertexBuffer.emplace_back(vertexBuffer);
		}

		void GLVAO::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			glBindVertexArray(m_vaoId);
			indexBuffer->Bind();
			m_indexBuffer = indexBuffer;
		}
	}
}