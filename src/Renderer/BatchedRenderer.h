#pragma once
#include "../Components/Camera.h"
#include "../Components/Light.h"
#include "../Components/Entity.h"
#include "EntityRenderer.h"
#include "RenderObject.h"
#include <map>
#include <vector>
namespace Lava {
	class BatchedRenderer {
	public:
		virtual ~BatchedRenderer() = default;
		virtual void Update(Scene* scene,glm::vec4 clipPlane) = 0;
		virtual void AddToBatch(Entity* entity) = 0;

	protected:
		std::map<MeshRenderer*, std::vector<Entity*>*> m_batchList;
		EntityRenderer* m_renderer;
	};
}