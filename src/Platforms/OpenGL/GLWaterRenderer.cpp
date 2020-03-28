#include "GLWaterRenderer.h"

Lava::OpenGL::GLWaterRenderer::GLWaterRenderer(Scene* scene) : WaterRenderer(scene)
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
	m_bufferLayout->uniform_count = 3;
	
	m_vao = new GLVAO();
	m_vbo = CreateRef<GLVertexBuffer>(m_planeVertices, m_planeVertexCount);
	m_vbo->SetBufferElements(m_bufferLayout, &layoutCount);
	m_vao->AddVertexBufferObject(m_vbo,0);

	fbos = new GLFrameBuffers();
}

Lava::OpenGL::GLWaterRenderer::~GLWaterRenderer()
{
	delete m_shaderBank;
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
}

void Lava::OpenGL::GLWaterRenderer::CompleteRender()
{
}

void Lava::OpenGL::GLWaterRenderer::Update(Scene* scene)
{
}

void Lava::OpenGL::GLWaterRenderer::InitReflectionAndRefractionFrameBuffers()
{
	m_reflectionFbo = fbos->CreateFrameBuffer();
	m_reflectionColorTexId = fbos->CreateColorTextureAttachment(m_reflectionWidth,m_reflectionHeight);
	m_reflectionDepthBuffer = fbos->CreateDepthBufferAttachment(m_reflectionWidth, m_reflectionHeight);
	fbos->UnbindFrameBuffer();
	
	m_refractionFbo = fbos->CreateFrameBuffer();
	m_refractionColorTexId = fbos->CreateColorTextureAttachment(m_refractionWidth, m_refractionHeight);
	m_refractionDepthTexId = fbos->CreateDepthTextureAttachment(m_refractionWidth, m_refractionHeight);
	fbos->UnbindFrameBuffer();
}
