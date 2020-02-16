#include "GLSkyboxRenderer.h"
#include "../../Core/AssetDatabase.h"
Lava::OpenGL::GLSkyboxRenderer::GLSkyboxRenderer(Scene* scene,float size) :SkyboxRenderer(scene), SIZE(size)
{
	m_bank = new GLShaderBank();
	LoadShaders();
	m_bank->Activate();
	int count = 1;
	m_bufferLayout = new VertexBufferElement();
	m_bufferLayout->uniform_name = "position";
	m_bufferLayout->uniform_count = 3;

	m_cubemapTextureId = Lava::AssetDatabase::LoadCubeMap(m_skyboxTextures);
	m_vao = new GLVAO();
	m_vbo = CreateRef<GLVertexBuffer>(m_vertices, 108);
	m_vbo->SetBufferElements(m_bufferLayout, &count);
	m_vao->AddVertexBufferObject(m_vbo, 0);
}

Lava::OpenGL::GLSkyboxRenderer::~GLSkyboxRenderer()
{
	delete m_bank;
}

void Lava::OpenGL::GLSkyboxRenderer::Configure(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	m_bank->Bind();
	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;
	m_bank->GetShader(0)->SetMatrix4x4("View", viewMatrix);
	m_bank->GetShader(0)->SetMatrix4x4("Projection", projectionMatrix);
}

void Lava::OpenGL::GLSkyboxRenderer::CompleteRender()
{
	m_bank->Unbind();
}

void Lava::OpenGL::GLSkyboxRenderer::Update(Scene* scene)
{
	Configure(m_scene->ActiveCamera->GetViewMatrix(), m_scene->ActiveCamera->GetProjectionMatrix());
	m_vao->Bind();
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTextureId);
	glDrawArrays(GL_TRIANGLES, 0, 108);
	glDisableVertexAttribArray(0);
	m_vao->Unbind();
	CompleteRender();
}

void Lava::OpenGL::GLSkyboxRenderer::LoadShaders()
{
	auto vertexShader = new GLShader("Shaders/Skybox.vp", ShaderType::Vertex, m_bank);
	auto fragmentShader = new GLShader("Shaders/Skybox.fp", ShaderType::Fragment, m_bank);
	m_bank->AddShader(vertexShader);
	m_bank->AddShader(fragmentShader);
}