#include <Gl/glew.h>
#include <glfw3.h>
#include "GLRenderer.h"
#include "../../Utils/Debug.h"
#include <iostream>
namespace Lava {
	namespace OpenGL {
		GLRenderer::GLRenderer(std::vector<GLShader*> shader_list)
		{
			if (shader_list.size() == 0)
				LoadDefaultShader(shader_list);

			m_bank = new GLShaderBank();
			for(int i=0;i<shader_list.size();i++)
				m_bank->AddShader(shader_list[i]);

			m_bank->Activate();
		}

		GLRenderer::~GLRenderer()
		{
			delete m_bank;
		}

		void GLRenderer::Update()
		{
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_bank->Bind();
			for (int i = 0; i < m_renderlist.size(); i++)
			{
				m_renderlist[i]->m_vao->Bind();
				EnableAttributesForRenderObject(i);

				glDrawElements(GL_TRIANGLES, m_renderlist[i]->m_mesh.m_posCount, GL_UNSIGNED_INT, 0);

				DisableAttributesForRenderObject(i);
				m_renderlist[i]->m_vao->Unbind();
			}
			m_bank->Unbind();
		}

		void GLRenderer::LoadDefaultShader(std::vector<GLShader*>& list)
		{
			auto vert = new GLShader("Shaders/vertexShader.vp", ShaderType::Vertex);
			auto frag = new GLShader("Shaders/fragmentShader.fp", ShaderType::Fragment);
			list.push_back(vert);
			list.push_back(frag);
		}

	}
}