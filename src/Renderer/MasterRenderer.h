#pragma once
#include "../Core/Scene.h"
#include "BatchedRenderer.h"
#include "SkyboxRenderer.h"
#include "WaterRenderer.h"
#include "ParticleRenderer.h"
namespace Lava
{
	class MasterRenderer {
	public:
		EntityRenderer* nonbatchedRenderer;
		BatchedRenderer* batchedRenderer;
		SkyboxRenderer* skyboxRenderer;
		WaterRenderer* waterRenderer;
		ParticleRenderer* particleRenderer;
		virtual void InternalUpdate() = 0;
		MasterRenderer(Scene* scene) : m_scene(scene),nonbatchedRenderer(nullptr),batchedRenderer(nullptr),
								skyboxRenderer(nullptr),waterRenderer(nullptr),
								particleRenderer(nullptr){ }
		void Update(glm::vec4 clipPlane) {
			InternalUpdate();
			nonbatchedRenderer->Update(m_scene);
			batchedRenderer->Update(m_scene, clipPlane);
			skyboxRenderer->Update(m_scene);
			particleRenderer->Update(m_scene);
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