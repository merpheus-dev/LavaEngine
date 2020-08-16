#pragma once
#include <GL/glew.h>
#include <glfw3.h>
#include "../../Renderer/QuadRenderer.h"
#include "GLShaderBank.h"
#include "../../Core/WindowManager.h"
#include "GLPostProcessingEffect.h"
namespace Lava {
	namespace OpenGL {
		class GLQuadRenderer : public QuadRenderer {
			// Inherited via QuadRenderer
			virtual void Setup() override;
			virtual void Render(unsigned int* renderTargets,unsigned int count) override;
			virtual ~GLQuadRenderer();
		};
	}
}