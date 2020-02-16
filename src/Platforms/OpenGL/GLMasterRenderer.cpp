#include "GLMasterRenderer.h"

void Lava::OpenGL::GLMasterRenderer::InternalUpdate()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glClearColor(m_scene->FogColor.x, m_scene->FogColor.y, m_scene->FogColor.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
