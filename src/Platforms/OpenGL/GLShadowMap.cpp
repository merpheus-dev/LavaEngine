#include "GLShadowMap.h"

Lava::OpenGL::GLShadowMap::GLShadowMap() : shadowMapFbo(0), shadowMapTextureId(0)
{
	glGenBuffers(1, &shadowMapFbo);
	GenerateShadowTexture();
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMapTextureId, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); //unbind /w 0
}

void Lava::OpenGL::GLShadowMap::GenerateShadowTexture()
{
	glGenTextures(1, &shadowMapTextureId);
	glBindTexture(GL_TEXTURE_2D, shadowMapTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOWRES_WIDTH, SHADOWRES_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}
