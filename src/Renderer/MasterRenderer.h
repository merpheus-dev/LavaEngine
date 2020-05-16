#pragma once
#include "../Core/Scene.h"
#include "BatchedRenderer.h"
#include "SkyboxRenderer.h"
#include "WaterRenderer.h"
#include "ParticleRenderer.h"
#include "NonbatchedRenderer.h"
namespace Lava
{
	class MasterRenderer {
	public:
		NonbatchedRenderer* nonbatchedRenderer;
		BatchedRenderer* batchedRenderer;
		SkyboxRenderer* skyboxRenderer;
		WaterRenderer* waterRenderer;
		ParticleRenderer* particleRenderer;
		virtual void InternalUpdate() = 0;
		MasterRenderer(Scene* scene) : m_scene(scene), nonbatchedRenderer(nullptr), batchedRenderer(nullptr),
			skyboxRenderer(nullptr), waterRenderer(nullptr),
			particleRenderer(nullptr) 
		{
		}
		void Update(glm::vec4 clipPlane) {
			InternalUpdate();
			batchedRenderer->Update(m_scene, clipPlane);
			skyboxRenderer->Update(m_scene);
			particleRenderer->Update(m_scene);
			auto cam_data = m_scene->ActiveCamera->GetCameraData();
			nonbatchedRenderer->Render(cam_data);
		}
	public:
		Scene* GetScenePtr()
		{
			return m_scene;
		}
	protected:
		Scene* m_scene;
	};
}