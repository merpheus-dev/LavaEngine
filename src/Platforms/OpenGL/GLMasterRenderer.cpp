#include "GLMasterRenderer.h"

void Lava::OpenGL::GLMasterRenderer::setup_frame_buffers()
{
	glGenFramebuffers(1, &renderSceneFbo);

	glGenTextures(1, &colorBufferTextureId);
	glBindTexture(GL_TEXTURE_2D, colorBufferTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WindowManager::Width(), WindowManager::Height(),
		0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //F* off gamma!

	glGenRenderbuffers(1, &renderSceneDepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderSceneDepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WindowManager::Width(), WindowManager::Height());

	glBindFramebuffer(GL_FRAMEBUFFER, renderSceneFbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferTextureId, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderSceneDepthBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Lava::OpenGL::GLMasterRenderer::setup_water_renderer(Transform* water_transform)
{
	waterRenderer = new GLWaterRenderer(m_scene, water_transform);
}

void Lava::OpenGL::GLMasterRenderer::InternalUpdate()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glClearColor(m_scene->scene_data->fog_color.x, m_scene->scene_data->fog_color.y, m_scene->scene_data->fog_color.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void Lava::OpenGL::GLMasterRenderer::InternalUpdateEnd()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	screenQuadRenderer->Render(colorBufferTextureId);
}

void Lava::OpenGL::GLMasterRenderer::ShadowPassUpdate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, renderSceneFbo);
	InternalUpdate();
}

void Lava::OpenGL::GLMasterRenderer::AttachPostProcessingEffect(GLPostProcessingEffect* postfx)
{
	screenQuadRenderer->postProcessingEffects.push_back(postfx);
}
