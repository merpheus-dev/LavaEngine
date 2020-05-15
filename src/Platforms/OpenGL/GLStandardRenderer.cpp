#include "GLStandardRenderer.h"
#include "GLShaderBank.h"

namespace Lava
{
	namespace OpenGL
	{
		GLStandardRenderer::GLStandardRenderer(Scene* scene, std::vector<GLShader*> shader_list)
			: EntityRenderer(scene)
		{
			m_bank = new GLShaderBank();
			if (shader_list.empty())
				LoadDefaultShader(shader_list);
			for (auto& shader : shader_list)
				m_bank->AddShader(shader);

			m_bank->Activate();
		}

		GLStandardRenderer::~GLStandardRenderer()
		{
			delete m_bank;
		}

		void GLStandardRenderer::Configure(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
		{
			m_bank->Bind();
			m_bank->GetShader(0)->SetMatrix4x4("View", viewMatrix);
			m_bank->GetShader(0)->SetMatrix4x4("Projection", projectionMatrix);
		}

		void GLStandardRenderer::CompleteRender()
		{
			m_bank->Unbind();
		}

		void GLStandardRenderer::Update(Scene* scene)
		{
			Configure(scene->ActiveCamera->GetViewMatrix(), scene->ActiveCamera->GetProjectionMatrix());
			SetLightInfo(scene);
			SetFogInfo();
			Render(dummy_render_parameter,glm::vec4(0));
			CompleteRender();
		}

		void GLStandardRenderer::BindAttribute(int variableIndex, const char* variableName)
		{
			m_bank->AddVariable(variableIndex, variableName);
		}

		void GLStandardRenderer::SetLightInfo(Scene* scene)
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

		void GLStandardRenderer::SetFogInfo()
		{
			m_bank->GetShader(0)->SetFloat1("FogDensity", m_scene->scene_data->fog_density);
			m_bank->GetShader(1)->SetFloat3("FogColor", m_scene->scene_data->fog_color);
		}

		void GLStandardRenderer::PushInstanceData(Entity* entityPtr)
		{
			auto model = entityPtr->transform->GetTransformationMatrix();
			m_bank->GetShader(0)->SetMatrix4x4("Model", model);
			m_bank->GetShader(1)->SetFloat1("Shininess", entityPtr->material->shininess);
			m_bank->GetShader(1)->SetFloat1("GlossDamping", entityPtr->material->glossDamping);
		}

		void GLStandardRenderer::BindObjects(Entity* entityPtr)
		{
			GLRenderObject* renderObjectPtr = (GLRenderObject*)(entityPtr->GetMeshRenderer(Platform::OpenGL)->GetRenderObject());
			renderObjectPtr->m_vao->Bind();

			for (auto i = 0; i < entityPtr->mesh->m_bufferLayoutCount; i++)
				glEnableVertexAttribArray(i);

			if (renderObjectPtr->HasTexture()) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entityPtr->material->m_mainTexture->texture_id);
				m_bank->GetShader(1)->SetInt1("textureSampler", 0);
			}

			if (renderObjectPtr->HasNormalMap()) {
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, entityPtr->material->m_nrmTexture->texture_id);
				m_bank->GetShader(1)->SetInt1("normalMapSampler", 1);
			}
		}

		void GLStandardRenderer::UnBindObjects(Entity* entityPtr)
		{
			for (auto i = 0; i < entityPtr->mesh->m_bufferLayoutCount; i++)
				glDisableVertexAttribArray(i);
			GLRenderObject* renderObjectPtr = static_cast<GLRenderObject*>(entityPtr->GetMeshRenderer(Platform::OpenGL)->GetRenderObject());
			renderObjectPtr->m_vao->Unbind();
		}

		void GLStandardRenderer::Render(std::map<MeshRenderer*, std::vector<Entity*>*>& entities, glm::vec4 clipPlane)
		{
			glEnable(GL_CLIP_DISTANCE0);
			for (auto& render_element : m_renderlist) {
				BindObjects(render_element);
				PushInstanceData(render_element);
				m_bank->GetShader(0)->SetFloat4("ClipPlane", clipPlane);
				glDrawElements(GL_TRIANGLES, render_element->mesh->m_posCount, GL_UNSIGNED_INT, 0);
				UnBindObjects(render_element);
			}
			glDisable(GL_CLIP_DISTANCE0);
		}

		void GLStandardRenderer::LoadDefaultShader(std::vector<GLShader*>& list)
		{
			auto vert = new GLShader("Shaders/vertexShader.vp", ShaderType::Vertex, m_bank);
			auto frag = new GLShader("Shaders/fragmentShader.fp", ShaderType::Fragment, m_bank);
			list.push_back(vert);
			list.push_back(frag);
		}
	}
}
