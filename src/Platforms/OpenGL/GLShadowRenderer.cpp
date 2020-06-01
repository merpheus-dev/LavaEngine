#include "GLShadowRenderer.h"

void Lava::OpenGL::GLShadowRenderer::Setup(Scene* scene)
{
	m_scene = scene;
	m_bank = new GLShaderBank();
	auto vert = new GLShader("Shaders/ShadowMap.vp", ShaderType::Vertex, m_bank);
	auto frag = new GLShader("Shaders/ShadowMap.fp", ShaderType::Fragment, m_bank);
	m_bank->AddShader(vert);
	m_bank->AddShader(frag);
	m_bank->Activate();

	m_bank->AddVariable(0, "position");
	m_shadowMap = new GLShadowMap();
}

void Lava::OpenGL::GLShadowRenderer::Render(CameraData& data)
{
	glCullFace(GL_FRONT);
	m_bank->Bind();
	PrepareFrameData(data);
	for (auto* entity : entity_list) {
		BindObject(entity);
		auto model_matrix = entity->transform->GetTransformationMatrix();
		m_bank->GetShader(0)->SetMatrix4x4("Model", model_matrix);
		glDrawElements(GL_TRIANGLES, entity->mesh->m_posCount, GL_UNSIGNED_INT, 0);
		UnbindObject(entity);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, WindowManager::Width(), WindowManager::Height());
	m_bank->Unbind();
	glCullFace(GL_BACK);
}

void Lava::OpenGL::GLShadowRenderer::PrepareFrameData(CameraData& data)
{
	auto lightProjection = glm::ortho(-size, size, -size, size, near_plane, far_plane);
	auto light_ptr = m_scene->scene_data->lights->at(0);
	auto lightViewMatrix = glm::lookAt(m_scene->scene_data->lights->at(0)->Position,
		glm::vec3(0),
		glm::vec3(0., 1., 0.));

	lightSpaceMatrix = lightProjection * lightViewMatrix;
	data.LightSpaceMatrix = lightSpaceMatrix;
	data.ShadowMapTextureId = m_shadowMap->shadowMapTextureId;

	m_bank->GetShader(0)->SetMatrix4x4("LightSpaceMatrix", lightSpaceMatrix);
	glViewport(0, 0, m_shadowMap->SHADOWRES_WIDTH, m_shadowMap->SHADOWRES_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, m_shadowMap->shadowMapFbo);
	glClear(GL_DEPTH_BUFFER_BIT);

}

Lava::OpenGL::GLShadowRenderer::~GLShadowRenderer()
{
	delete m_bank;
}

void Lava::OpenGL::GLShadowRenderer::BindObject(Entity* entity)
{
	auto renderObjectPtr = (GLRenderObject*)(entity->GetMeshRenderer(Platform::OpenGL)->GetRenderObject());
	renderObjectPtr->m_vao->Bind();
	EnableAttributesForRenderObject(entity);
	if (renderObjectPtr->HasTexture()) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity->material->m_mainTexture->texture_id);
	}
}

void Lava::OpenGL::GLShadowRenderer::UnbindObject(Entity* entity)
{
	DisableAttributesForRenderObject(entity);
	((GLRenderObject*)(entity->GetMeshRenderer(Platform::OpenGL)->GetRenderObject()))->m_vao->Unbind();
}

void Lava::OpenGL::GLShadowRenderer::EnableAttributesForRenderObject(Entity* entity)
{
	glEnableVertexAttribArray(0); //position only
}

void Lava::OpenGL::GLShadowRenderer::DisableAttributesForRenderObject(Entity* entity)
{
	glDisableVertexAttribArray(0);
}
