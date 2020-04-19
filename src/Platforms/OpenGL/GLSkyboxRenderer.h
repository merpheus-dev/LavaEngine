#pragma once
#include "../../Renderer/SkyboxRenderer.h"
#include "GLShaderBank.h"
#include "GLMeshData.h"
#include <memory>
namespace Lava {
	namespace OpenGL {
		class GLSkyboxRenderer :public SkyboxRenderer {
		public:
			GLSkyboxRenderer(Scene* scene,float size,std::vector<const char*>& skybox_textures);
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
			std::vector<const char*>& m_skyboxTextures;
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