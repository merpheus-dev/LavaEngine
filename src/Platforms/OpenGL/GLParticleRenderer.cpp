#include "GLParticleRenderer.h"

Lava::OpenGL::GLParticleRenderer::GLParticleRenderer(Scene* scene)
: ParticleRenderer(scene)
{
	m_bank = new GLShaderBank();
	LoadShaders();
	m_bank->Activate();
	int count = 1;
	m_bufferLayout = new VertexBufferElement();
	m_bufferLayout->uniform_name = "position";
	m_bufferLayout->uniform_count = 2;

	m_vao = new GLVAO();
	m_vbo = CreateRef<GLVertexBuffer>(m_vertices, 8);
	m_vbo->SetBufferElements(m_bufferLayout, &count);
	m_vao->AddVertexBufferObject(m_vbo, 0);
}

Lava::OpenGL::GLParticleRenderer::~GLParticleRenderer()
{
	delete m_bank;
	delete m_vao;
	delete m_bufferLayout;
}

void Lava::OpenGL::GLParticleRenderer::AttachParticleSystem(ParticleSystem* particle_system)
{
	m_systems.push_back(particle_system);
}

void Lava::OpenGL::GLParticleRenderer::Configure(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	m_bank->Bind();
	m_bank->GetShader(0)->SetMatrix4x4("Projection", projectionMatrix);
}

void Lava::OpenGL::GLParticleRenderer::CompleteRender()
{
	m_bank->Unbind();
}

void Lava::OpenGL::GLParticleRenderer::Update(Scene* scene)
{
	if (m_systems.empty()) return;
	Configure(m_scene->ActiveCamera->GetViewMatrix(), m_scene->ActiveCamera->GetProjectionMatrix());
	m_vao->Bind();
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //=>GL_ONE_MINUS_SRC_ALPHA
	glDepthMask(false);
	RenderInternal();
	glDepthMask(true);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	m_vao->Unbind();
	CompleteRender();
}

void Lava::OpenGL::GLParticleRenderer::LoadShaders()
{
	auto vs = new GLShader("Shaders/Particle.vp", ShaderType::Vertex, m_bank);
	auto fs = new GLShader("Shaders/Particle.fp", ShaderType::Fragment, m_bank);
	m_bank->AddShader(vs);
	m_bank->AddShader(fs);
}

void Lava::OpenGL::GLParticleRenderer::RenderInternal()
{
	for(auto& particleSystem:m_systems)
	{
		for (auto& particle : particleSystem->particles)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, particle->texturePtr->id);
			m_bank->GetShader(0)->SetMatrix4x4("ModelView",
				particle->GetFacingTransformationMatrix(m_scene->ActiveCamera->GetViewMatrix()));

			m_bank->GetShader(0)->SetFloat2("currentSheetOffset", particle->current_sheet_offset);
			m_bank->GetShader(0)->SetFloat2("nextSheetOffset", particle->next_sheet_offset);
			m_bank->GetShader(0)->SetFloat1("blendFactor", particle->sheet_blend);
			m_bank->GetShader(0)->SetFloat1("rowCount", particle->texturePtr->number_of_rows);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); //8=>vert count of per particle quad
		}
	}
}
