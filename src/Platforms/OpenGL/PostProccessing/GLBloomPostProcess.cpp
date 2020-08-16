#include "GLBloomPostProcess.h"

void Lava::OpenGL::GLBloomPostProcess::Init()
{
	m_bank = new GLShaderBank();
	auto vert2 = new GLShader("Shaders/postProcess.vp", ShaderType::Vertex, m_bank);
	auto frag2 = new GLShader(shaderPath, ShaderType::Fragment, m_bank);
	m_bank->AddShader(vert2);
	m_bank->AddShader(frag2);
	m_bank->Activate();
	m_bank->AddVariable(0, "position");

	blurBank = new GLShaderBank();
	auto vert3 = new GLShader("Shaders/postProcess.vp", ShaderType::Vertex, blurBank);
	auto frag3 = new GLShader("Shaders/gaussian.fp", ShaderType::Fragment, blurBank);
	blurBank->AddShader(vert3);
	blurBank->AddShader(frag3);
	blurBank->Activate();
	blurBank->AddVariable(0, "position");

	glGenFramebuffers(2, pingPongFbos);
	glGenTextures(2, pingPongTextures);
	for (uint32_t i = 0; i < 2; ++i)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingPongFbos[i]);
		glBindTexture(GL_TEXTURE_2D, pingPongTextures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WindowManager::Width(), WindowManager::Height(),
			0, GL_RGBA, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingPongTextures[i], 0);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Final image
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

void Lava::OpenGL::GLBloomPostProcess::Render(unsigned int renderTargets[], bool last)
{
	bool horizontal = true;
	for(uint32_t i=0;i<10;++i)
	{
		glBindFramebuffer(GL_FRAMEBUFFER,pingPongFbos[horizontal]);
		blurBank->Bind();
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, i==0 ? renderTargets[1] : pingPongTextures[!horizontal]);
		blurBank->GetShader(1)->SetBool("horizontal",horizontal);
		blurBank->GetShader(1)->SetInt1("colorTexture", 3);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		blurBank->Unbind();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		horizontal = !horizontal;
	}
	
	if (!last)
		glBindFramebuffer(GL_FRAMEBUFFER, renderTargetID);
	m_bank->Bind();
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, renderTargets[0]);
	m_bank->GetShader(1)->SetInt1("scene", 3);
	glActiveTexture(GL_TEXTURE4);
	m_bank->GetShader(1)->SetInt1("bloomTex", 4);
	glBindTexture(GL_TEXTURE_2D, pingPongTextures[!horizontal]); //!horizontal cuz we are flipping at the end of loop above
	m_bank->GetShader(1)->SetFloat1("exposure", 1.f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	m_bank->Unbind();
	if (!last)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
