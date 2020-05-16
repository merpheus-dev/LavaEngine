#include "GLNonbatchedRenderer.h"

void Lava::OpenGL::GLNonbatchedRenderer::Setup(Scene* scene)
{
	m_scene = scene;
	//Add shaders
	m_bank = new GLShaderBank();
	auto vert = new GLShader("Shaders/vertexShader.vp", ShaderType::Vertex, m_bank);
	auto frag = new GLShader("Shaders/fragmentShader.fp", ShaderType::Fragment, m_bank);
	m_bank->AddShader(vert);
	m_bank->AddShader(frag);
	m_bank->Activate();

	//VAO Pointers
	m_bank->AddVariable(0, "position");
	m_bank->AddVariable(1, "texCoord");
	m_bank->AddVariable(2, "normal");
	m_bank->AddVariable(3, "tangent");
}

void Lava::OpenGL::GLNonbatchedRenderer::Render(CameraData& data)
{
	m_bank->Bind();
	PrepareFrameData(data);
	glEnable(GL_CLIP_DISTANCE0);
	for (auto* entity : entity_list) {
		BindObject(entity);
		auto model_matrix = entity->transform->GetTransformationMatrix();
		m_bank->GetShader(0)->SetMatrix4x4("Model", model_matrix);
		m_bank->GetShader(1)->SetFloat1("Shininess", entity->material->shininess);
		m_bank->GetShader(1)->SetFloat1("GlossDamping", entity->material->glossDamping);

		glDrawElements(GL_TRIANGLES, entity->mesh->m_posCount, GL_UNSIGNED_INT, 0);
		UnbindObject(entity);
	}
	glDisable(GL_CLIP_DISTANCE0);
	m_bank->Unbind();
}

void Lava::OpenGL::GLNonbatchedRenderer::PrepareFrameData(CameraData& data)
{
	//Camera Data
	m_bank->GetShader(0)->SetMatrix4x4("View", data.View);
	m_bank->GetShader(0)->SetMatrix4x4("Projection", data.Projection);

	//Light Data
	m_bank->GetShader(1)->SetFloat1("AmbientLightIntensity", m_scene->scene_data->ambient_light_intensity);

	for (int i = 0; i < m_scene->scene_data->lights->size(); i++) {
		auto& light = m_scene->scene_data->lights->at(i);
		m_bank->GetShader(0)->SetFloat3(("LightPosition[" + std::to_string(i) + "]").c_str(), light->Position);
		m_bank->GetShader(1)->SetFloat3(("LightColor[" + std::to_string(i) + "]").c_str(), light->Color);
		m_bank->GetShader(1)->SetFloat3(("LightAttenuation[" + std::to_string(i) + "]").c_str(), light->Attenuation);
		m_bank->GetShader(1)->SetFloat1(("LightIntensity[" + std::to_string(i) + "]").c_str(), light->Intensity);
	}

	//Fog Data
	m_bank->GetShader(0)->SetFloat1("FogDensity", m_scene->scene_data->fog_density);
	m_bank->GetShader(1)->SetFloat3("FogColor", m_scene->scene_data->fog_color);
}

Lava::OpenGL::GLNonbatchedRenderer::~GLNonbatchedRenderer()
{
	delete m_bank;
}

void Lava::OpenGL::GLNonbatchedRenderer::BindObject(Entity* entity)
{
	GLRenderObject* renderObjectPtr = (GLRenderObject*)(entity->GetMeshRenderer(Platform::OpenGL)->GetRenderObject());
	renderObjectPtr->m_vao->Bind();
	EnableAttributesForRenderObject(entity);
	if (renderObjectPtr->HasTexture()) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity->material->m_mainTexture->texture_id);
		m_bank->GetShader(1)->SetInt1("textureSampler", 0);
	}

	if (renderObjectPtr->HasNormalMap()) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, entity->material->m_nrmTexture->texture_id);
		m_bank->GetShader(1)->SetInt1("normalMapSampler", 1);
	}
}

void Lava::OpenGL::GLNonbatchedRenderer::EnableAttributesForRenderObject(Entity* entity)
{
	((GLRenderObject*)(entity->GetMeshRenderer(Platform::OpenGL)->GetRenderObject()))
		->EnableAttributes();
}

void Lava::OpenGL::GLNonbatchedRenderer::DisableAttributesForRenderObject(Entity* entity)
{
	((GLRenderObject*)(entity->GetMeshRenderer(Platform::OpenGL)->GetRenderObject()))
		->DisableAttributes();
}

void Lava::OpenGL::GLNonbatchedRenderer::UnbindObject(Entity* entity)
{
	DisableAttributesForRenderObject(entity);
	((GLRenderObject*)(entity->GetMeshRenderer(Platform::OpenGL)->GetRenderObject()))->m_vao->Unbind();
}
