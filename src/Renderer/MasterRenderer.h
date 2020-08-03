#pragma once
#include "../Core/Scene.h"
#include "BatchedRenderer.h"
#include "SkyboxRenderer.h"
#include "WaterRenderer.h"
#include "ParticleRenderer.h"
#include "NonbatchedRenderer.h"
#include "QuadRenderer.h"
namespace Lava
{
	class MasterRenderer {
	public:
		NonbatchedRenderer* shadowRenderer;
		NonbatchedRenderer* nonbatchedRenderer;
		BatchedRenderer* batchedRenderer;
		SkyboxRenderer* skyboxRenderer;
		WaterRenderer* waterRenderer;
		ParticleRenderer* particleRenderer;
		QuadRenderer* screenQuadRenderer;

		virtual void InternalUpdate() = 0;
		virtual void InternalUpdateEnd() = 0;
		virtual void ShadowPassUpdate() = 0;
		MasterRenderer(Scene* scene) : m_scene(scene), nonbatchedRenderer(nullptr), batchedRenderer(nullptr),
			skyboxRenderer(nullptr), waterRenderer(nullptr),
			particleRenderer(nullptr),shadowRenderer(nullptr), screenQuadRenderer(nullptr)
		{
		}
		void Update(glm::vec4 clipPlane) {
			auto cam_data = m_scene->ActiveCamera->GetCameraData();
			InternalUpdate();
			shadowRenderer->Render(cam_data);
			ShadowPassUpdate(); // Bind fbo
			batchedRenderer->Update(m_scene, clipPlane);
			skyboxRenderer->Update(m_scene);
			particleRenderer->Update(m_scene);
			nonbatchedRenderer->Render(cam_data);
			InternalUpdateEnd();
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