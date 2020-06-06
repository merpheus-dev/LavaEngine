#include "GLQuadRenderer.h"

void Lava::OpenGL::GLQuadRenderer::Setup()
{
	glGenVertexArrays(1, &k_vao);
	glGenBuffers(1, &k_vbo);
	glBindVertexArray(k_vao);
	glBindBuffer(GL_ARRAY_BUFFER, k_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));

	m_bank = new GLShaderBank();
	auto vert = new GLShader("Shaders/hdr.vp", ShaderType::Vertex, m_bank);
	auto frag = new GLShader("Shaders/hdr.fp", ShaderType::Fragment, m_bank);
	m_bank->AddShader(vert);
	m_bank->AddShader(frag);
	m_bank->Activate();
	m_bank->AddVariable(0, "position");
	//m_bank->AddVariable(1, "texCoord");
}

void Lava::OpenGL::GLQuadRenderer::Render(unsigned int& targetTextureId)
{
	m_bank->Bind();
	glBindVertexArray(k_vao);
	glEnableVertexAttribArray(0);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, targetTextureId);
	m_bank->GetShader(1)->SetInt1("hdrTexture", 3);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glEnable(GL_DEPTH_TEST);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	m_bank->Unbind();
}

Lava::OpenGL::GLQuadRenderer::~GLQuadRenderer()
{
	delete m_bank;
}
