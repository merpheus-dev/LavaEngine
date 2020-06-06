#pragma once
#include <GL/glew.h>
#include <glfw3.h>
#include "../../Renderer/QuadRenderer.h"
#include "GLShaderBank.h"
namespace Lava {
	namespace OpenGL {
		class GLQuadRenderer : public QuadRenderer {
			// Inherited via QuadRenderer
			virtual void Setup() override;
			virtual void Render(unsigned int& targetTextureId) override;
			virtual ~GLQuadRenderer();
		private:
			GLShaderBank* m_bank;
		};
	}
}