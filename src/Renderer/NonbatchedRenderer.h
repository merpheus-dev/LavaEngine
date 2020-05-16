#pragma once
#include <vector>
#include "../Components/Entity.h"
#include "../Core/Data/CameraData.h"
#include "../Core/Scene.h"
#include "../Core/Data/SceneData.h"
namespace Lava {

	class NonbatchedRenderer {
	public:
		virtual ~NonbatchedRenderer() = default;
		virtual void Setup(Scene* scene) = 0;
		virtual void Render(CameraData& data) = 0;
		virtual void PrepareFrameData(CameraData& data) = 0;
		virtual void BindObject(Entity* entity) = 0;
		virtual void UnbindObject(Entity* entity) = 0;
		std::vector<Entity*> entity_list;
		Scene* m_scene;

	private:
		virtual void EnableAttributesForRenderObject(Entity* entity) = 0;
		virtual void DisableAttributesForRenderObject(Entity* entity) = 0;

	};
}