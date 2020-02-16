#pragma once
#include "../../Renderer/SkyboxRenderer.h"
#include "GLShaderBank.h"
#include "GLMeshData.h"
#include <memory>
namespace Lava {
	namespace OpenGL {
		class GLSkyboxRenderer :public SkyboxRenderer {
		public:
			GLSkyboxRenderer(Scene* scene,float size);
			~GLSkyboxRenderer();
			virtual void Configure(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) override;
			virtual void CompleteRender() override;
			virtual void Update(Scene* scene) override;
			virtual void LoadShaders() override;

		private:
			GLShaderBank* m_bank;
			GLVAO* m_vao;
			VertexBufferElement* m_bufferLayout;

			std::shared_ptr<GLVertexBuffer> m_vbo;
			unsigned int m_cubemapTextureId;

		private:
			const float SIZE;
			std::vector<const char*> m_skyboxTextures = {
				"Assets/sky/right.png","Assets/sky/left.png","Assets/sky/top.png","Assets/sky/bottom.png","Assets/sky/back.png","Assets/sky/front.png"
			};
			float* m_vertices = new float[108]{
				-SIZE,  SIZE, -SIZE,
				-SIZE, -SIZE, -SIZE,
				 SIZE, -SIZE, -SIZE,
				 SIZE, -SIZE, -SIZE,
				 SIZE,  SIZE, -SIZE,
				-SIZE,  SIZE, -SIZE,

				-SIZE, -SIZE,  SIZE,
				-SIZE, -SIZE, -SIZE,
				-SIZE,  SIZE, -SIZE,
				-SIZE,  SIZE, -SIZE,
				-SIZE,  SIZE,  SIZE,
				-SIZE, -SIZE,  SIZE,

				 SIZE, -SIZE, -SIZE,
				 SIZE, -SIZE,  SIZE,
				 SIZE,  SIZE,  SIZE,
				 SIZE,  SIZE,  SIZE,
				 SIZE,  SIZE, -SIZE,
				 SIZE, -SIZE, -SIZE,

				-SIZE, -SIZE,  SIZE,
				-SIZE,  SIZE,  SIZE,
				 SIZE,  SIZE,  SIZE,
				 SIZE,  SIZE,  SIZE,
				 SIZE, -SIZE,  SIZE,
				-SIZE, -SIZE,  SIZE,

				-SIZE,  SIZE, -SIZE,
				 SIZE,  SIZE, -SIZE,
				 SIZE,  SIZE,  SIZE,
				 SIZE,  SIZE,  SIZE,
				-SIZE,  SIZE,  SIZE,
				-SIZE,  SIZE, -SIZE,

				-SIZE, -SIZE, -SIZE,
				-SIZE, -SIZE,  SIZE,
				 SIZE, -SIZE, -SIZE,
				 SIZE, -SIZE, -SIZE,
				-SIZE, -SIZE,  SIZE,
				 SIZE, -SIZE,  SIZE
			};

		};
	}
}