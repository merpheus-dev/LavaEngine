#include "GLWaterRenderer.h"

Lava::OpenGL::GLWaterRenderer::GLWaterRenderer(Scene* scene, Transform* transform)
												: WaterRenderer(scene), m_transform(transform)
{
	m_shaderBank = new GLShaderBank();
	auto vertexShaderId = new GLShader("Shaders/water.vp", ShaderType::Vertex, m_shaderBank);
	auto fragShaderId = new GLShader("Shaders/water.fp", ShaderType::Fragment, m_shaderBank);
	m_shaderBank->AddShader(vertexShaderId);
	m_shaderBank->AddShader(fragShaderId);
	m_shaderBank->Activate();
	auto layoutCount = 1;
	m_bufferLayout = new VertexBufferElement();
	m_bufferLayout->uniform_name = "position";
	m_bufferLayout->uniform_count = 2;

	m_vao = new GLVAO();
	m_vbo = CreateRef<GLVertexBuffer>(m_planeVertices, m_planeVertexCount);
	m_vbo->SetBufferElements(m_bufferLayout, &layoutCount);
	m_vao->AddVertexBufferObject(m_vbo, 0);

	fbos = new GLFrameBuffers();
}

Lava::OpenGL::GLWaterRenderer::~GLWaterRenderer()
{
	delete m_shaderBank;
}

int Lava::OpenGL::GLWaterRenderer::BindReflectionFbo()
{
	fbos->BindFrameBuffer(m_reflectionFbo, m_reflectionWidth, m_reflectionHeight);
	return m_reflectionColorTexId;
}

int Lava::OpenGL::GLWaterRenderer::BindRefractionFbo()
{
	fbos->BindFrameBuffer(m_refractionFbo, m_refractionWidth, m_refractionHeight);
	return m_refractionColorTexId;
}

void Lava::OpenGL::GLWaterRenderer::UnbindAll()
{
	fbos->UnbindFrameBuffer();
}

void Lava::OpenGL::GLWaterRenderer::SetReflectionDimensions(int width, int height)
{
	m_reflectionWidth = width;
	m_reflectionHeight = height;
}

void Lava::OpenGL::GLWaterRenderer::SetRefractionDimensions(int width, int height)
{
	m_refractionWidth = width;
	m_refractionHeight = height;
}

void Lava::OpenGL::GLWaterRenderer::Configure(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	m_shaderBank->Bind();
	m_shaderBank->GetShader(0)->SetMatrix4x4("View", viewMatrix);
	m_shaderBank->GetShader(0)->SetMatrix4x4("Projection", projectionMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_reflectionColorTexId);
	m_shaderBank->GetShader(1)->SetInt1("reflectionTexture", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_refractionColorTexId);
	m_shaderBank->GetShader(1)->SetInt1("refractionTexture", 1);
}

void Lava::OpenGL::GLWaterRenderer::CompleteRender()
{
	m_shaderBank->Unbind();
}

void Lava::OpenGL::GLWaterRenderer::Update(Scene* scene)
{
	Configure(scene->ActiveCamera->GetViewMatrix(), scene->ActiveCamera->GetProjectionMatrix());
	m_vao->Bind();
	glEnableVertexAttribArray(0);
	m_shaderBank->GetShader(0)->SetMatrix4x4("Model", m_transform->GetTransformationMatrix());
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glDisableVertexAttribArray(0);
	m_vao->Unbind();
	CompleteRender();
}

void Lava::OpenGL::GLWaterRenderer::InitReflectionAndRefractionFrameBuffers()
{
	m_reflectionFbo = fbos->CreateFrameBuffer();
	m_reflectionColorTexId = fbos->CreateColorTextureAttachment(m_reflectionWidth, m_reflectionHeight);
	m_reflectionDepthBuffer = fbos->CreateDepthBufferAttachment(m_reflectionWidth, m_reflectionHeight);
	fbos->UnbindFrameBuffer();

	m_refractionFbo = fbos->CreateFrameBuffer();
	m_refractionColorTexId = fbos->CreateColorTextureAttachment(m_refractionWidth, m_refractionHeight);
	m_refractionDepthTexId = fbos->CreateDepthTextureAttachment(m_refractionWidth, m_refractionHeight);
	fbos->UnbindFrameBuffer();
}
