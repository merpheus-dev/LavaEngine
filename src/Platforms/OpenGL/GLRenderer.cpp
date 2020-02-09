#include <Gl/glew.h>
#include <glfw3.h>
#include "GLRenderer.h"
#include "../../Utils/Debug.h"
#include <iostream>
#include "../Platform.h"
namespace Lava {
	namespace OpenGL {
		GLRenderer::GLRenderer(Scene* scene, std::vector<GLShader*> shader_list)
		{
			m_bank = new GLShaderBank();
			m_scene = scene;

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

		void GLRenderer::Configure(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
		{
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			glCullFace(GL_BACK);
			glClearColor(m_scene->FogColor.x, m_scene->FogColor.y, m_scene->FogColor.z, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_bank->Bind();

			m_bank->GetShader(0)->SetMatrix4x4("View", viewMatrix);
			m_bank->GetShader(0)->SetMatrix4x4("Projection", projectionMatrix);
		}

		void GLRenderer::SetLightInfo(Light& light)
		{
			m_bank->GetShader(0)->SetFloat3("LightPosition", light.Position);
			m_bank->GetShader(1)->SetFloat3("LightColor", light.Color);
		}

		void GLRenderer::SetFogInfo()
		{
			m_bank->GetShader(0)->SetFloat1("FogDensity", m_scene->FogDensity);
			m_bank->GetShader(1)->SetFloat3("FogColor", m_scene->FogColor);
		}

		void GLRenderer::CompleteRender()
		{
			m_bank->Unbind();
		}

		void GLRenderer::PushInstanceData(Entity* entityPtr)
		{
			auto model = entityPtr->transform->GetTransformationMatrix();
			m_bank->GetShader(0)->SetMatrix4x4("Model", model);
			m_bank->GetShader(1)->SetFloat1("Shininess", entityPtr->material->shininess);
			m_bank->GetShader(1)->SetFloat1("GlossDamping", entityPtr->material->glossDamping);
		}

		void GLRenderer::BindObjects(Entity* entityPtr)
		{
			GLRenderObject* renderObjectPtr = (GLRenderObject*)(entityPtr->GetMeshRenderer(Platform::OpenGL)->GetRenderObject());
			renderObjectPtr->m_vao->Bind();
			EnableAttributesForRenderObject(entityPtr);
			if(renderObjectPtr->HasTexture())
				glBindTexture(GL_TEXTURE_2D, entityPtr->material->m_mainTexture->texture_id);

		}

		void GLRenderer::UnBindObjects(Entity* entityPtr)
		{
			DisableAttributesForRenderObject(entityPtr);
			((GLRenderObject*)(entityPtr->GetMeshRenderer(Platform::OpenGL)->GetRenderObject()))->m_vao->Unbind();
		}

		void GLRenderer::Render(std::map<MeshRenderer*, std::vector<Entity*>*>& entities)
		{
			for (auto& batchedPack : entities) {
				BindObjects((*(batchedPack.second))[0]);
				for (auto& batchedEntity : (*(batchedPack.second))) {
					PushInstanceData(batchedEntity);
					glDrawElements(GL_TRIANGLES, batchedEntity->mesh->m_posCount, GL_UNSIGNED_INT, 0);
				}
				UnBindObjects((*(batchedPack.second))[0]);
			}
		}


		void GLRenderer::Update(Camera camera, Light light)
		{
			for (int i = 0; i < m_renderlist.size(); i++)
			{
				BindObjects(m_renderlist[i]);
				//if (renderObjectPtr->HasTexture())

				UnBindObjects(m_renderlist[i]);
			}
			CompleteRender();
		}

		void GLRenderer::BindAttribute(int variableIndex, const char* variableName)
		{
			m_bank->AddVariable(variableIndex, variableName);
		}

		void GLRenderer::LoadDefaultShader(std::vector<GLShader*>& list)
		{
			auto vert = new GLShader("Shaders/vertexShader.vp", ShaderType::Vertex, m_bank);
			auto frag = new GLShader("Shaders/fragmentShader.fp", ShaderType::Fragment, m_bank);
			list.push_back(vert);
			list.push_back(frag);
		}
	}
}