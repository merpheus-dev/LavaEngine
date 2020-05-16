#pragma once
#include "../../Renderer/MasterRenderer.h"
#include "GLBatchedRenderer.h"
#include "GLSkyboxRenderer.h"
#include <vector>
#include "GLWaterRenderer.h"
#include "GLParticleRenderer.h"
#include "GLNonbatchedRenderer.h"
namespace Lava {
	namespace OpenGL
	{
		class GLMasterRenderer :public MasterRenderer {
		public:
			GLMasterRenderer(Scene* scene) : MasterRenderer(scene) {
				nonbatchedRenderer = new GLNonbatchedRenderer();
				nonbatchedRenderer->Setup(scene);

				batchedRenderer = new GLBatchedRenderer(m_scene, std::vector<GLShader*>());
				skyboxRenderer = new GLSkyboxRenderer(m_scene,500.0f,scene->scene_data->skybox_textures); //Culling should be disabled for the cube
				particleRenderer = new GLParticleRenderer(m_scene);
			}

			void setup_water_renderer(Transform* water_transform)
			{
				waterRenderer = new GLWaterRenderer(m_scene, water_transform);
			}
			
			virtual void InternalUpdate() override;
		};
	}
}
