#pragma once
#include "../Core/Scene.h"
#include "BatchedRenderer.h"
#include "SkyboxRenderer.h"
#include "WaterRenderer.h"
namespace Lava
{
	class MasterRenderer {
	public:
		BatchedRenderer* batchedRenderer;
		SkyboxRenderer* skyboxRenderer;
		WaterRenderer* waterRenderer;
		virtual void InternalUpdate() = 0;
		MasterRenderer(Scene* scene) : m_scene(scene),batchedRenderer(nullptr),skyboxRenderer(nullptr),waterRenderer(nullptr) {

		}
		void Update(glm::vec4 clipPlane) {
			InternalUpdate();
			batchedRenderer->Update(m_scene, clipPlane);
			skyboxRenderer->Update(m_scene);
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