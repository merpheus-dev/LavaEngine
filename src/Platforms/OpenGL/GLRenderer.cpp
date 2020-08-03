#include <Gl/glew.h>
#include <glfw3.h>
#include "GLRenderer.h"
#include "../../Utils/Debug.h"
#include <iostream>
#include "../Platform.h"
namespace Lava {
	namespace OpenGL {
		GLRenderer::GLRenderer(Scene* scene, std::vector<GLShader*> shader_list) : EntityRenderer(scene)
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

		void GLRenderer::Configure(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
		{
			m_bank->Bind();
			m_bank->GetShader(0)->SetMatrix4x4("View", viewMatrix);
			m_bank->GetShader(0)->SetMatrix4x4("Projection", projectionMatrix);
		}

		void GLRenderer::SetLightInfo(Scene* scene)
		{
			m_bank->GetShader(1)->SetFloat1("AmbientLightIntensity", scene->scene_data->ambient_light_intensity);
			for (int i = 0; i < scene->scene_data->lights->size(); i++) {
				auto& light = scene->scene_data->lights->at(i);
				m_bank->GetShader(0)->SetFloat3(("LightPosition[" + std::to_string(i) + "]").c_str(), light->Position);
				m_bank->GetShader(1)->SetFloat3(("LightColor[" + std::to_string(i) + "]").c_str(), light->Color);
				m_bank->GetShader(1)->SetFloat3(("LightAttenuation[" + std::to_string(i) + "]").c_str(), light->Attenuation);
				m_bank->GetShader(1)->SetFloat1(("LightIntensity[" + std::to_string(i) + "]").c_str(), light->Intensity);
			}
		}

		void GLRenderer::SetFogInfo()
		{
			m_bank->GetShader(0)->SetFloat1("FogDensity", m_scene->scene_data->fog_density);
			m_bank->GetShader(1)->SetFloat3("FogColor", m_scene->scene_data->fog_color);
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
			if (renderObjectPtr->HasTexture()) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entityPtr->material->m_mainTexture->texture_id);
				m_bank->GetShader(1)->SetInt1("textureSampler", 0);
			}
			m_bank->GetShader(1)->SetFloat3("Albedo",entityPtr->material->albedoColor);

			
			if (renderObjectPtr->HasNormalMap()) {
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, entityPtr->material->m_nrmTexture->texture_id);
				m_bank->GetShader(1)->SetInt1("normalMapSampler", 1);
			}
		}

		void GLRenderer::UnBindObjects(Entity* entityPtr)
		{
			DisableAttributesForRenderObject(entityPtr);
			((GLRenderObject*)(entityPtr->GetMeshRenderer(Platform::OpenGL)->GetRenderObject()))->m_vao->Unbind();
		}

		void GLRenderer::Render(std::map<MeshRenderer*, std::vector<Entity*>*>& entities, glm::vec4 clipPlane)
		{
			glEnable(GL_CLIP_DISTANCE0);
			for (auto& batchedPack : entities) {
				BindObjects((*(batchedPack.second))[0]);
				for (auto& batchedEntity : (*(batchedPack.second))) {
					PushInstanceData(batchedEntity);
					m_bank->GetShader(0)->SetFloat4("ClipPlane", clipPlane);
					glDrawElements(GL_TRIANGLES, batchedEntity->mesh->m_posCount, GL_UNSIGNED_INT, 0);
				}
				UnBindObjects((*(batchedPack.second))[0]);
			}
			glDisable(GL_CLIP_DISTANCE0);
		}

		void GLRenderer::Update(Scene* scene)
		{
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