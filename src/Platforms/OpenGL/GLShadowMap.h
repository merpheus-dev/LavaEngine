#pragma once
#include <gl/glew.h>
#include <glfw3.h>
#include "../../Core/WindowManager.h"
namespace Lava {
	namespace OpenGL {
		class GLShadowMap {
		public:
			unsigned int shadowMapFbo;
			unsigned int shadowMapTextureId;
			const int SHADOWRES_WIDTH = 2048;
			const int SHADOWRES_HEIGHT = 2048;
			GLShadowMap();
		private:
			void GenerateShadowTexture();
		};
	}
}