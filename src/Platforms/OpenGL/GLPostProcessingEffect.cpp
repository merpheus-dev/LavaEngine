#include "GLPostProcessingEffect.h"

void Lava::OpenGL::GLPostProcessingEffect::Init()
{
	m_bank = new GLShaderBank();
	auto vert2 = new GLShader("Shaders/postProcess.vp", ShaderType::Vertex, m_bank);
	auto frag2 = new GLShader(shaderPath, ShaderType::Fragment, m_bank);
	m_bank->AddShader(vert2);
	m_bank->AddShader(frag2);
	m_bank->Activate();
	m_bank->AddVariable(0, "position");

	glGenTextures(1, &colorTargetID);
	glBindTexture(GL_TEXTURE_2D, colorTargetID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WindowManager::Width(), WindowManager::Height(),
		0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenFramebuffers(1, &renderTargetID);
	glGenRenderbuffers(1, &depthTargetID);
	glBindRenderbuffer(GL_RENDERBUFFER, depthTargetID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WindowManager::Width(), WindowManager::Height());

	glBindFramebuffer(GL_FRAMEBUFFER, renderTargetID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTargetID, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthTargetID);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Lava::OpenGL::GLPostProcessingEffect::Render(unsigned int renderTargets[], bool last)
{
	if (!last)
		glBindFramebuffer(GL_FRAMEBUFFER, renderTargetID);
	m_bank->Bind();
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, renderTargets[0]);
	m_bank->GetShader(1)->SetInt1("colorTexture", 3);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	m_bank->Unbind();
	if (!last)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
