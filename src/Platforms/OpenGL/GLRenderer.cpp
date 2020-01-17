#include <Gl/glew.h>
#include <glfw3.h>
#include "GLRenderer.h"
#include "../../Utils/Debug.h"
#include <iostream>
namespace Lava {
	namespace OpenGL {
		GLRenderer::GLRenderer()
		{
		}

		GLRenderer::~GLRenderer()
		{
		}

		void GLRenderer::Update()
		{
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (int i = 0; i < m_renderlist.size(); i++)
			{
				m_renderlist[i]->m_vao->Bind();
				int vertexLayoutAttributeCount = m_renderlist[i]->m_mesh.m_bufferLayoutCount;
				for (int j = 0; j < vertexLayoutAttributeCount; j++) {
					glEnableVertexAttribArray(j);
				}
				glDrawElements(GL_TRIANGLES, m_renderlist[i]->m_mesh.m_posCount, GL_UNSIGNED_INT, 0);
				for (int j = 0; j < vertexLayoutAttributeCount; j++) {
					glDisableVertexAttribArray(j);
				}
				m_renderlist[i]->m_vao->Unbind();
			}
		}

	}
}