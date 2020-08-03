#pragma once
#include "../../Renderer/MasterRenderer.h"
#include "GLBatchedRenderer.h"
#include "GLSkyboxRenderer.h"
#include <vector>
#include "GLWaterRenderer.h"
#include "GLParticleRenderer.h"
#include "GLNonbatchedRenderer.h"
#include "GLShadowRenderer.h"
#include "GLQuadRenderer.h"
namespace Lava {
	namespace OpenGL
	{
		class GLMasterRenderer :public MasterRenderer {
		public:
			GLMasterRenderer(Scene* scene) : MasterRenderer(scene){
				setup_frame_buffers();
				screenQuadRenderer = new GLQuadRenderer();
				screenQuadRenderer->Setup();
				shadowRenderer = new GLShadowRenderer();
				shadowRenderer->Setup(scene);

				nonbatchedRenderer = new GLNonbatchedRenderer();
				nonbatchedRenderer->Setup(scene);
				nonbatchedRenderer->SetFrameBuffers(renderSceneFbo);

				batchedRenderer = new GLBatchedRenderer(m_scene, std::vector<GLShader*>());
				skyboxRenderer = new GLSkyboxRenderer(m_scene,500.0f,scene->scene_data->skybox_textures); //Culling should be disabled for the cube
				particleRenderer = new GLParticleRenderer(m_scene);
			}

			void setup_frame_buffers();

			void setup_water_renderer(Transform* water_transform);
			void AttachPostProcessingEffect(GLPostProcessingEffect* postfx);

			virtual void InternalUpdate() override;
			virtual void InternalUpdateEnd() override;
			virtual void ShadowPassUpdate() override;

		public:
			unsigned int colorBufferTextureId[2];
			unsigned int renderSceneFbo;
			unsigned int renderSceneDepthBuffer;
			// Inherited via MasterRenderer
		};
	}
}
