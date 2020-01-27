#pragma once
#include "../Components/Camera.h"
#include "../Components/Light.h"
#include "../Components/Entity.h"
#include "Renderer.h"
#include "RenderObject.h"
#include <map>
#include <vector>
namespace Lava {
	class BatchedRenderer {
	public:
		virtual ~BatchedRenderer() = default;
		virtual void Update(Camera camera, Light light) = 0;
		virtual void AddToBatch(Entity* entity) = 0;

	protected:
		std::map<MeshRenderer*, std::vector<Entity*>*> m_batchList;
		Renderer* m_renderer;
	};
}