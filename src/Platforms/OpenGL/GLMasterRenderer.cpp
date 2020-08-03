#include "GLMasterRenderer.h"

void Lava::OpenGL::GLMasterRenderer::setup_frame_buffers()
{
	glGenFramebuffers(1, &renderSceneFbo);
	glGenRenderbuffers(1, &renderSceneDepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderSceneDepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WindowManager::Width(), WindowManager::Height());
	glBindFramebuffer(GL_FRAMEBUFFER, renderSceneFbo);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderSceneDepthBuffer);

	const unsigned int bufferCount = sizeof(colorBufferTextureId) / sizeof(unsigned int);
	glGenTextures(bufferCount, colorBufferTextureId);
	for (unsigned int i = 0; i < bufferCount; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, colorBufferTextureId[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WindowManager::Width(), WindowManager::Height(),
			0, GL_RGBA, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBufferTextureId[i], 0);
	}

	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);
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
	screenQuadRenderer->Render(colorBufferTextureId[0]); //Render hdr MRT 0, MRT 1=> Bloom
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
