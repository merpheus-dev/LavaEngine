#include <Gl/glew.h>
#include <glfw3.h>
#include "GLRenderer.h"
#include "../../Utils/Debug.h"
#include <iostream>
#include "../Platform.h"
namespace Lava {
	namespace OpenGL {
		GLRenderer::GLRenderer(std::vector<GLShader*> shader_list)
		{
			m_bank = new GLShaderBank();

			if (shader_list.size() == 0)
				LoadDefaultShader(shader_list);

			for (int i = 0; i < shader_list.size(); i++)
				m_bank->AddShader(shader_list[i]);

			m_bank->Activate();
		}

		GLRenderer::~GLRenderer()
		{
			delete m_bank;
		}

		void GLRenderer::Update(Camera camera,Light light)
		{
			glEnable(GL_DEPTH_TEST);
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_bank->Bind();
			for (int i = 0; i < m_renderlist.size(); i++)
			{
				GLRenderObject* renderObjectPtr = (GLRenderObject*)(m_renderlist[i]->GetMeshRenderer(Platform::OpenGL)->GetRenderObject());
				renderObjectPtr->m_vao->Bind();

				EnableAttributesForRenderObject(i);

				auto view = GetViewMatrix(camera);
				auto proj = GetProjectionMatrix();
				auto model = m_renderlist[i]->transform->GetTransformationMatrix();

				m_bank->GetShader(0)->SetMatrix4x4("MVP", proj * view * model);

				m_bank->GetShader(0)->SetFloat3("LightPosition", light.Position);
				m_bank->GetShader(1)->SetFloat3("LightColor", light.Color);

				if (renderObjectPtr->HasTexture())
					glBindTexture(GL_TEXTURE_2D, m_renderlist[i]->material->m_mainTexture->texture_id);

				glDrawElements(GL_TRIANGLES, m_renderlist[i]->mesh->m_posCount, GL_UNSIGNED_INT, 0);

				DisableAttributesForRenderObject(i);
				renderObjectPtr->m_vao->Unbind();
			}
			m_bank->Unbind();
		}

		void GLRenderer::BindAttribute(int variableIndex, const char* variableName)
		{
			m_bank->AddVariable(variableIndex, variableName);
		}

		void GLRenderer::LoadDefaultShader(std::vector<GLShader*>& list)
		{
			auto vert = new GLShader("Shaders/vertexShader.vp", ShaderType::Vertex,m_bank);
			auto frag = new GLShader("Shaders/fragmentShader.fp", ShaderType::Fragment,m_bank);
			list.push_back(vert);
			list.push_back(frag);
		}
	}
}