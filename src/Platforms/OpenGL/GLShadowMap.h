#pragma once
#include <gl/glew.h>
#include <glfw3.h>
namespace Lava {
	namespace OpenGL {
		class GLShadowMap {
		public:
			unsigned int shadowMapFbo;
			unsigned int shadowMapTextureId;
			const int SHADOWRES_WIDTH = 1024;
			const int SHADOWRES_HEIGHT = 1024;
			GLShadowMap();
		private:
			void GenerateShadowTexture();
		};
	}
}