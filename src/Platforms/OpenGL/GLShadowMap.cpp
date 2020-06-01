#include "GLShadowMap.h"

Lava::OpenGL::GLShadowMap::GLShadowMap() : shadowMapFbo(0), shadowMapTextureId(0)
{
	glGenFramebuffers(1, &shadowMapFbo);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFbo);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	GenerateShadowTexture();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMapTextureId, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); //unbind /w 0
	glViewport(0, 0, WindowManager::Width(), WindowManager::Height());
}

void Lava::OpenGL::GLShadowMap::GenerateShadowTexture()
{
	glGenTextures(1, &shadowMapTextureId);
	glBindTexture(GL_TEXTURE_2D, shadowMapTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOWRES_WIDTH, SHADOWRES_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
